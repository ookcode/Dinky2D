//
//  Window.hpp
//  dinky2d
//
//  Created by Vincent Yao on 2017/7/16.
//  Copyright © 2017年 ookcode. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

namespace Dinky {
    
class Window {
public:
    Window(int argc, char** argv, float width, float height);
    ~Window();
    void show();
    
private:
    static void update(int value);
    static void mainloop();
};
    
}

#endif /* Window_hpp */
