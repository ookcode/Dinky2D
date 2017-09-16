//
//  TouchDelegate.h
//  dinky2d
//
//  Created by vincent on 2017/9/12.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef TouchDelegate_h
#define TouchDelegate_h

namespace Dinky {
    class TouchDelegate {
    public:
        virtual void onTouchBegin(int x, int y) = 0;
        virtual void onTouchMove(int x, int y) = 0;
        virtual void onTouchEnded(int x, int y) = 0;
    };
}

#endif /* TouchDelegate_h */
