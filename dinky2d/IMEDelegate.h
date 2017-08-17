//
//  IMEDelegate.h
//  dinky2d
//
//  Created by vincent on 2017/8/8.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef IMEDelegate_h
#define IMEDelegate_h

namespace Dinky {
    class IMEDelegate {
    public:
        virtual void onKeyDown(int key, bool isSpecialKey) = 0;
        virtual void onKeyUp(int key, bool isSpecialKey) = 0;
    };
}

#endif /* IMEDelegate_h */
