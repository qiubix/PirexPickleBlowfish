#ifndef TOKEN_LOADER_HPP
#define TOKEN_LOADER_HPP

class TokenLoader
{
public:
  static TokenLoader * getInstance();

protected:
  TokenLoader();

private:
  static TokenLoader * instance;
};

#endif // TOKEN_LOADER_HPP
