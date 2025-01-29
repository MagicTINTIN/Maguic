#include <string>

namespace Maguic
{
    class Window
    {
    private:
        std::string name_;
    public:
        Window(std::string name);
        ~Window();
    };
    
} // namespace Maguic
