//
//  CommonClasses.h
//  Snakes and Ladders
//
//  Created by Kuldeep Teekas on 28/08/15.
//
//


#ifndef __COMMONCLASSES_H__
#define __COMMONCLASSES_H__

struct ItemsDetailStruct{

    std::string m_heading;
    std::string m_imageURL;
    std::string m_content;
    
    ItemsDetailStruct(){
    
        m_heading = "";
        m_imageURL = "";
        m_content = "";
    }
};

enum CONTENT_TYPE{
    CONTENT_LATEST_POST,
    CONTENT_SSB_GUIDE,
    CONTENT_NOTIFICATIONS
};

#endif // __COMMONCLASSES_H__
