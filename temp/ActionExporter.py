# ======================================================================================
# File         : ActionExporter.py
# Author       : Wu Jie 
# Last Change  : 08/11/2010 | 14:32:15 PM | Wednesday,August
# Description  : 
# ======================================================================================

#/////////////////////////////////////////////////////////////////////////////
# imports
#/////////////////////////////////////////////////////////////////////////////

import sys

#/////////////////////////////////////////////////////////////////////////////
# funtions
#/////////////////////////////////////////////////////////////////////////////

# ------------------------------------------------------------------ 
# Desc: 
# ------------------------------------------------------------------ 

def main():
    import getopt
    import os.path

    src_file = "./Action.xml"
    dest_dir = "./Action"

    try:
        opts, args = getopt.getopt(sys.argv[1:], 'lfqd:x:')
    except getopt.error, msg:
        print msg
        print "usage: python ActionExporter.py [-f src_file] [-d dest_dir]"
        print "-f: load source xml (default: Action.xml)"
        print "-d: save to the dest directory (default: ./Action)"
        sys.exit(2)
    for o, a in opts:
        if o == '-f': src_file = a
        if o == '-d': dest_dir = a

    if os.path.isfile ( src_file ) == False:
        print "can't find source file %s" % src_file
        return 0

    # the original attribute names
    attrNames = [ 
            "biaozhu", "id", 
            "actionid_left", "actionid_right", "actionloop", "play_pace", "continuancetimer", "endtype", "control", 
            "ms_type_0", "ms_data0_0", "ms_data1_0", "ms_data2_0", "ms_data3_0", "ms_data4_0", "ms_data5_0", "ms_data6_0", 
            "ms_type_1", "ms_data0_1", "ms_data1_1", "ms_data2_1", "ms_data3_1", "ms_data4_1", "ms_data5_1", "ms_data6_1", 
            "ms_type_2", "ms_data0_2", "ms_data1_2", "ms_data2_2", "ms_data3_2", "ms_data4_2", "ms_data5_2", "ms_data6_2", 
            "ms_type_3", "ms_data0_3", "ms_data1_3", "ms_data2_3", "ms_data3_3", "ms_data4_3", "ms_data5_3", "ms_data6_3", 
            "ms_type_4", "ms_data0_4", "ms_data1_4", "ms_data2_4", "ms_data3_4", "ms_data4_4", "ms_data5_4", "ms_data6_4", 
            "gesture_0", "gesture_1", "gesture_2", "gesture_3", "gesture_4",
            "actionbuff_0", "actionbuff_1", "actionbuff_2", "actionbuff_3", "actionbuff_4",
            "effect0", "effect1", "effect2", "effect3", "effect4",
            "x_effext0", "x_effext1", "x_effext2", 
            "zhendong0", "zhendong1", "zhendong2", "zhendong3", "zhendong4", 
            "magic0", "magic1", "magic2", "magic3", "magic4",
            "fectearthef_right0", "fectearthef_left0", "fectsecond0", "fectearthef_right1", "fectearthef_left1", "fectsecond1", "fectearthef_right2", "fectearthef_left2", "fectsecond2",
            "mtlcolor0", "mtlcolor1", "mtlcolor2", "mtlcolor3", "mtlcolor4",
            "sms", "sfx", "scale_timer", "scale",
            ]
    # attribute need convert to the new name
    import re;

    # parse the src dom
    import xml.dom.minidom
    print u"parsing xml file %s..." % src_file
    dom = xml.dom.minidom.parse(src_file)
    elements = dom.getElementsByTagName("Mapping")

    # init re patterns
    pattern_mstype = re.compile(r'ms_type_(\d)')
    pattern_msdata = re.compile(r'ms_data(\d)_(\d)')
    pattern_gesture = re.compile(r'gesture_(\d)')
    pattern_actionbuff = re.compile(r'actionbuff_(\d)')
    pattern_effect = re.compile(r'effect(\d)')
    pattern_x_effect = re.compile(r'x_effext(\d)')
    pattern_zhendong = re.compile(r'zhendong(\d)')
    pattern_magic = re.compile(r'magic(\d)')
    pattern_fectearthef_right = re.compile(r'fectearthef_right(\d)')
    pattern_fectearthef_left = re.compile(r'fectearthef_left(\d)')
    pattern_fectsecond = re.compile(r'fectsecond(\d)')
    pattern_mtlcolor = re.compile(r'mtlcolor(\d)')

    # init list
    # ERROR multi-demension array can't use this, it will use reference for all the 5: movekey_list = [['0']*7]*5
    movekey_list = []
    for i in range(5):
        movekey_list.append(['0']*7)
    gesture_list = ['0']*5
    actionbuff_list = ['0']*5
    effect_list = ['0']*5
    x_effext_list = ['0']*3
    zhendong_list = ['0']*5
    magic_list = ['0']*5
    fectearthef_right_list = ['0']*3
    fectearthef_left_list = ['0']*3
    fectsecond_list = ['0']*3
    mtlcolor_list = ['0']*5

    pattern_list = [ 
            (gesture_list,pattern_gesture,'m_sznPose'),
            (effect_list,pattern_effect,'m_sznNEffect'),
            (x_effext_list,pattern_x_effect,'m_sznXEffect'),
            (magic_list,pattern_magic,'m_sznMagic'),
            (mtlcolor_list,pattern_mtlcolor,'m_sznMtlColor'),
            (zhendong_list,pattern_zhendong,'m_sznZhenDong'),
            (fectearthef_left_list,pattern_fectearthef_left,'m_sznLeftHitGround'),
            (fectearthef_right_list,pattern_fectearthef_right,'m_sznRightHitGround'),
            (actionbuff_list,pattern_actionbuff,'__actionbuff_list'),
            (fectsecond_list,pattern_fectsecond,'__fectsecond_list'),
            ]

    attr_converter = {
            "biaozhu" : "m_tag",
            "id" : "m_ID",
            "actionid_left" : "m_nActionLeft",
            "actionid_right" : "m_nActionRight",
            "play_pace" : "m_nPlaySpeed",
            "actionloop" : "m_bActionLoop",
            "continuancetimer" : "m_nMContinueTimer",
            "endtype" : "m_eMEndType",
            "control" : "m_bKeyOpen",
            "sms" : "m_nLockMagic"
            }

    # save each element 
    num = len(elements)
    progress = 0
    for el in elements:
        # create new element
        new_dom = xml.dom.minidom.getDOMImplementation().createDocument( None, "doc", None )
        root = new_dom.createElement( "Root" )
        new_el = new_dom.createElement( "CActionData" )
        root.appendChild(new_el)
        new_el.setAttribute("m_version",'0')

        # analysis old xml data. 
        for attr_name in attrNames:
            attr_value = el.getAttribute(attr_name).strip()

            # skip keys
            re_result = pattern_mstype.match(attr_name)
            if re_result:
                continue

            # move keys
            re_result = pattern_msdata.match(attr_name)
            if re_result:
                data_idx, movekey_idx = re_result.group(1,2) 
                movekey_list[int(movekey_idx)][int(data_idx)] = attr_value
                continue

            # other pattern list
            found = False
            for pattern_info in pattern_list:
                re_result = pattern_info[1].match(attr_name)
                if re_result:
                    i = re_result.group(1) 
                    pattern_info[0][int(i)] = attr_value
                    found = True
                    break
            if found:
                continue

            # rename tag
            new_name = attr_name
            if attr_converter.has_key(attr_name):
                new_name = attr_converter[attr_name]
            new_el.setAttribute(new_name,attr_value)

        # establish movekey_list elements
        idx = 0
        el_movekey_list = new_dom.createElement ("m_szMKey")
        for param_list in movekey_list:
            el_param_list = new_dom.createElement ( "idx_" + str(idx) )
            el_param_list.setAttribute ( "eType", str(idx) )

            el_params = new_dom.createElement ("params")
            el_param_list.appendChild(el_params)
            idx_param = 0
            for param in param_list:
                el_params.setAttribute ( "idx_" + str(idx_param), str(param) )
                idx_param += 1
            el_movekey_list.appendChild(el_param_list)
            idx += 1
        new_el.appendChild(el_movekey_list)

        # establish other list
        # pattern_info 0: list, 1: regex, 2: 
        for pattern_info in pattern_list:
            el_list = new_dom.createElement (pattern_info[2])
            idx = 0
            for value in pattern_info[0]:
                el_list.setAttribute ( "idx_" + str(idx), value )
                idx += 1
            new_el.appendChild(el_list)

        # create file name
        # tagName = el.getAttribute ("biaozhu")
        id = el.getAttribute ("id")
        # filename = id.strip() + "_" + tagName + ".xml"
        filename = id.strip() + ".xml"

        # do save
        if os.path.isdir(dest_dir) == False :
            print "dest path not found, create the path."
            os.makedirs (dest_dir)
            print "dest path %s created!" % dest_dir
        print u"%.2f saving file %s..." % (float(progress)/float(num), filename)
        progress += 1


        xml_text = '<?xml version="1.0" encoding="utf-8"?>\n'
        xml_text += root.toprettyxml("\t", "\n", "utf-8")
        open( os.path.join(dest_dir,filename), "wb").write(xml_text)
    # 
    dom.unlink()
    return 1

#/////////////////////////////////////////////////////////////////////////////
# run
#/////////////////////////////////////////////////////////////////////////////

if __name__ == "__main__":
    exit_status = int(not main())
    sys.exit(exit_status)
