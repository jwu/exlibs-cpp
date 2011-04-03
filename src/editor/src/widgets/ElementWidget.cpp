// ======================================================================================
// File         : ElementWidget.cpp
// Author       : Wu Jie 
// Last Change  : 04/04/2010 | 15:04:33 PM | Sunday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "editor.h"
#include "ElementWidget.h"
#include "EditorMain.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ParseThread::ParseThread ( QObject* _parent )
    : QThread (_parent)
    , m_abort (false)
    , m_needParse (false)
    , m_dirToParse ("")
    , m_parseType ("")
    , m_treeWidget (NULL)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ParseThread::~ParseThread ()
{
    m_mutex.lock();
    m_treeWidget = NULL;
    m_abort = true;
    m_mutex.unlock();
    wait();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ParseThread::init ( QTreeWidget* _treeWidget )
{
    m_treeWidget = _treeWidget;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ParseThread::parse ( const QString& _dataType, const QString& _dirPath )
{
    Q_ASSERT_X ( m_treeWidget, "addtoParse", "please call init first" );
    if ( !m_treeWidget )
        return;

    QMutexLocker locker(&m_mutex);
    if ( m_dirToParse != _dirPath ) {
        m_dirToParse = _dirPath;
        m_needParse = true;
    }
    m_parseType = _dataType;

    // run the thread if first trigger
    if ( !isRunning() ) {
        start ( LowestPriority );
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ParseThread::parseFile ( const QString& _filepath )
{
    int result = -1;
    if ( m_parseType == "ActionData" ) {
        result = this->parseAction ( _filepath );
    }

    return result;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ParseThread::parseAction ( const QString& _filepath )
{
    ex::XmlSerializeNode loadNode;
    loadNode.loadFromFile ( qPrintable(_filepath) );
    TestData* testData = ex_new TestData();
    EX_SERIALIZE( &loadNode, testData->getClassName(), *testData );

    // if this is a valid action element
    if ( testData->ID() != -1 && testData->tag() != ex::string_t::null ) {
        ElementItem* item = new ElementItem();
        item->setText ( 0, QString::number(testData->ID()) ); 
        item->setCheckState ( 0, Qt::Unchecked ); 
        item->setFlags ( item->flags() & ~Qt::ItemIsUserCheckable ); 
        item->setText ( 1, QString::fromUtf8(testData->tag().c_str()) ); 
        item->setPropObj ( ex::SmartPtr<ex::PropertyObject>(testData) ); 

        // it is possible we abort the programme with thread still running.
        if ( m_treeWidget ) {
            m_treeWidget->addTopLevelItem (item);
            return 0;
        }
        else {
            return 1; // need break the thread
        }
    }

    return -1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ParseThread::run()
{
    forever {
        if ( m_abort )
            return;

        if ( m_needParse == false ) {
            this->msleep(1000);
            return;
        }
        m_mutex.lock();
        m_needParse = false;
        m_mutex.unlock();

        // TODO: use progress bar

        //
        QDir dir (m_dirToParse);
        ex_log ( "parse directory: %s\n", qPrintable(dir.dirName()) );
        m_mutex.lock();
        m_mutex.unlock();

        QStringList files = dir.entryList();
        for (int i = 0; i < files.count(); ++i) {
            if ( m_abort == true )
                break;

            QString filename = files.at(i);
            if ( filename == "." || filename == ".." )
                continue;
            if ( filename.rightRef(4) != ".xml" )
                continue;

            QString absFilepath = dir.absoluteFilePath(filename); 

            // now we parse the file item
            // ex_log ( "start parsing dom content...\n" );
            int result = parseFile (absFilepath);
            switch (result) {
            case -1:
                ex_warning ("failed to parse config file: %s", qPrintable(filename) );
                break;
            case 1:
                m_abort = true;
                exit (0);
                break;
            }
        }
        m_treeWidget->resizeColumnToContents (1);
    }
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ElementItem::ElementItem ()
    : m_regen (false)
    , m_dirty (false)
{
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

QList<ex::PropertyInstanceBase::smart_ptr_t>& ElementItem::propInstList () { 
    if ( m_regen ) {
        m_propInstList.clear();
        this->addPropInst_recursively( m_propObj->getDescriptor() );
        m_regen = false;
    }
    return m_propInstList;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementItem::addPropInst_recursively ( const ex::PropertiesDescriptor* _desc )
{
    const ex::PropertiesDescriptor* parentDesc = _desc->parentDescriptor();
    if ( parentDesc )
        this->addPropInst_recursively ( parentDesc );

    //
    const ex::PropertiesDescriptor::properties_t& props = _desc->properties();
    for ( ex::PropertiesDescriptor::properties_t::c_iterator iter = props.begin(); iter != props.end(); ++iter ) {
        ex::PropertyInstanceBase::smart_ptr_t propInst = (*iter)->createPropertyInstance_sp(m_propObj.ptr());
        m_propInstList.push_back(propInst);
    }
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ElementWidget::ElementWidget ( QWidget* _pParent )
    : QWidget (_pParent)
{
    setupUi(this);

    filter->setHint(tr("<Filter>"));

    // signal slot
    connect( filter, SIGNAL(filterChanged(const QString&)), this, SLOT(applyFilter(const QString&)) );
    connect( elementView, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)) );
    connect( elementView, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(checkReset(QTreeWidgetItem*,int)) );
    connect( elementView, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(updateItem(QTreeWidgetItem*)) );

    // init tree view
    elementView->header()->setMovable(false);
    elementView->header()->setResizeMode(QHeaderView::Interactive);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ElementWidget::~ElementWidget ()
{
    this->deinit ();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ElementWidget::init ()
{
    ex_log ("init ElementWidget\n");

    //
    m_parseThread.init ( elementView );
    saveButton->setDisabled(true);
    saveAllButton->setDisabled(true);

    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::deinit ()
{
    ex_log ("deinit ElementWidget\n");

    // stop the pending-item-thread
    if ( m_parseThread.isRunning() )
    {
        m_parseThread.abort();
        m_parseThread.quit();
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::explore ( const QString& _dataType, const QString& _dirPath )
{
    // check if the file is valid
    QFileInfo fileInfo (_dirPath);
    ex_assert_return ( fileInfo.isDir(), /*void*/, "the path %s is not a directory.", _dirPath );
    m_editDir = _dirPath;

    // add to parse thread
    m_parseThread.parse (_dataType,_dirPath);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::checkReset ( QTreeWidgetItem* _item, int _column )
{
    if ( _column != 0 )
        return;

    if ( _item->checkState(0) == Qt::Unchecked ) {
        ElementItem* elItem = static_cast<ElementItem*>(_item);
        if ( elItem->isDirty() ) {
            this->reset(_item);
        }
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::onSave ()
{
    QTreeWidgetItem* item = elementView->currentItem();
    ex_log ("start saving item %s ...\n", qPrintable(item->text(1)) );
    saveItem (item);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::onSaveAll ()
{
    ex_log ("start saving all changed items ...\n" );
    int count = 0;
    for ( int i = 0; i < elementView->topLevelItemCount(); ++i ) {
        QTreeWidgetItem* item = elementView->topLevelItem(i);
        ElementItem* elItem = static_cast<ElementItem*>(item);
        if ( elItem->isDirty()  ) {
            ex_log (" |-start saving item %s ...", qPrintable(item->text(1)) );
            saveItem (item);
            ex_log ("done!\n");
            ++count;
        }
    }
    saveAllButton->setDisabled(true);
    ex_log ("%d item(s) saved.\n", count );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::saveItem ( QTreeWidgetItem* _item )
{
    this->replace(_item);
    ElementItem* elItem = static_cast<ElementItem*>(_item);

    // save item to the xml file.
    {
        ex::XmlSerializeNode saveNode ( ex::XmlNode::smart_ptr_t(ex_new ex::XmlNode("Root") ) );
        EX_SERIALIZE ( &saveNode, elItem->propObj()->getClassName(), *(elItem->propObj().ptr()) );
        saveNode.saveToFile ( qPrintable(m_editDir + "/" + elItem->text(0) + ".xml") );
    }

    _item->setCheckState ( 0, Qt::Unchecked ); 
    emit currentItemSaved(_item);

    elItem->setDirty(false);
    updateItem (_item);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::updateItem ( QTreeWidgetItem* _item )
{
    this->blockSignals(true);
    ElementItem* elItem = static_cast<ElementItem*>(_item);
    if ( elItem->isDirty() ) {
        elItem->setCheckState ( 0, Qt::Checked ); 
        elItem->setFlags ( elItem->flags() | Qt::ItemIsUserCheckable ); 
        saveButton->setDisabled(false);
        saveAllButton->setDisabled(false); // TODO: yes, I know saveAll can only enable, but can't be disabled unless you trigger saveAll slot. 
    }
    else {
        elItem->setCheckState ( 0, Qt::Unchecked ); 
        elItem->setFlags ( elItem->flags() & ~Qt::ItemIsUserCheckable ); 
        saveButton->setDisabled(true);
    }
    this->blockSignals(false);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::reset ( QTreeWidgetItem* _item )
{
    typedef QList<ex::PropertyInstanceBase::smart_ptr_t> inst_list_t; 
    ElementItem* elItem = static_cast<ElementItem*>(_item);
    inst_list_t& instList = elItem->propInstList();
    for ( inst_list_t::iterator iter = instList.begin(); iter != instList.end(); ++iter ) {
        (*iter)->reset();
    }
    emit currentItemReseted(_item);
    elItem->setDirty(false);
    updateItem (_item);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::replace ( QTreeWidgetItem* _item )
{
    typedef QList<ex::PropertyInstanceBase::smart_ptr_t> inst_list_t; 
    ElementItem* elItem = static_cast<ElementItem*>(_item);
    inst_list_t& instList = elItem->propInstList();
    for ( inst_list_t::iterator iter = instList.begin(); iter != instList.end(); ++iter ) {
        (*iter)->replace();
    }
    emit currentItemReplaced(_item);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::applyFilter ( const QString& _pattern )
{
    elementView->setUpdatesEnabled(false);
    const bool matchAll = _pattern.isEmpty();
    for ( int i = 0; i < elementView->topLevelItemCount(); ++i )
    {
        QTreeWidgetItem* item = elementView->topLevelItem(i);
        const QString tagName = item->text(1);
        const bool show = matchAll || tagName.contains(_pattern, Qt::CaseInsensitive);
        item->setHidden( show == false );
    }
    elementView->setUpdatesEnabled(true);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ElementWidget::doLuaFilter () {
    elementView->setUpdatesEnabled(false);
    for ( int i = 0; i < elementView->topLevelItemCount(); ++i )
    {
        QTreeWidgetItem* item = elementView->topLevelItem(i);

        bool show = true;

        // parse lua script
        luaL_loadfile ( ex::lua::state(), ex::path_t("e:/project/dev/exlibs/src/editor/_res/lua/lua_filter.lua").c_str() );
        if ( lua_pcall ( ex::lua::state(), 0, 0, 0 ) != 0 ) {
            ex_error ( "failed to load lua script" );
        }

        // exec filter function
        lua_getglobal( ex::lua::state(), "filter" );
        if ( lua_pcall ( ex::lua::state(), 0, 0, 0 ) != 0 ) {
            ex_error ( "error running function 'filter': %s", lua_tostring( ex::lua::state(), -1 ) );
        }

        // const bool show = TODO: apply-lua-filter here! 
        item->setHidden( show == false );
    }
    elementView->setUpdatesEnabled(true);
}
