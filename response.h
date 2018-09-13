//
// Created by benoit on 18/09/13.
//

#ifndef SIMPLEHTTP_RESPONSE_H
#define SIMPLEHTTP_RESPONSE_H

#include <string>
#include <sstream>

namespace bobnet {
    class Response {
    public:
        Response(): buffer_() {}

        std::string text() const { return buffer_.str(); }

        // This is called to add data at the end of our buffer.
        void add_data(char* data, size_t size);
    private:
        std::stringstream buffer_;

    };
}

#endif //SIMPLEHTTP_RESPONSE_H
