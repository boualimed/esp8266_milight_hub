#ifndef _PATTERNHANDLER_H
#define _PATTERNHANDLER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <functional>
#include <TokenIterator.h>

class UrlTokenBindings {
public:
  UrlTokenBindings(TokenIterator& patternTokens, TokenIterator& requestTokens);

  bool hasBinding(const char* key) const;
  const char* get(const char* key) const;

private:
  TokenIterator& patternTokens;
  TokenIterator& requestTokens;
};

class PatternHandler : public RequestHandler {
public:
  typedef std::function<void(UrlTokenBindings*)> TPatternHandlerFn;

  PatternHandler(const String& pattern,
    const HTTPMethod method,
    const TPatternHandlerFn fn);

  ~PatternHandler();

  bool canHandle(HTTPMethod requestMethod, String requestUri) override;
  bool handle(ESP8266WebServer& server, HTTPMethod requesetMethod, String requestUri) override;

private:
  char* _pattern;
  TokenIterator* patternTokens;
  const HTTPMethod method;
  const PatternHandler::TPatternHandlerFn fn;
};

#endif
