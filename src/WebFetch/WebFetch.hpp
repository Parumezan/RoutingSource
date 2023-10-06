#ifndef WEBFETCH_HPP_
#define WEBFETCH_HPP_

#include "Console.hpp"
#include "Includes.hpp"

namespace RoutingSource
{
    class WebFetch
    {
        private:
            std::shared_ptr<Console> _console;

        protected:
            curlpp::Cleanup _cleaner;
            curlpp::Easy _request;

        public:
            WebFetch(std::shared_ptr<Console> console);
            ~WebFetch();
            std::string fetchData(std::string url);
            void fetchImg(std::string filePath, std::string url);
    };
} // namespace RoutingSource

#endif /* !WEBFETCH_HPP_ */