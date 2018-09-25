#include <iostream>
#include "Rover.h"

namespace Rover
{
    class Test {
        private:
            int m_width;
            int m_height;
            std::String m_str
            Grid m_grid;
            std::String expectedStr;
            std::String expectedPath;

        public:
            Test(int width, int height, std::String str, std::String expErr, std::String expPath) {
                m_width = width;
                m_height = height;
                m_str = str;
                expectedStr = exp;
                expectedPath = expPath;
            }
            
            bool execute() {
                
                try {
                    Rover::RoverMapper mapper(m_width, m_height, m_str);
                    auto result = mapper.getPath(start, end);
                } catch(std::exception const & e){
                    if(e.what() != expectedStr) {
                        cout << "Test Failed" << std::endl;
                        return FALSE;
                    } else {
                        cout << "Test Passed" << std::endl;
                        return TRUE;
                    }
                }

                if(result == expectedPath) {
                    cout << "Test Passed" << std::endl;
                    return TRUE;
                } else {
                    cout << "Test Failed" << std::endl;
                    return FALSE;
                }
            }
    }
}
