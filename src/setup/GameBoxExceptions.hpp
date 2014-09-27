#ifndef GAME_BOX_EXCEPTIONS_HPP
#define GAME_BOX_EXCEPTIONS_HPP

class NoSuchArmyInBoxException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "There is no such army in the box.";
  }
};

class ThereIsAlreadySuchArmyInTheBoxException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "There is already such army in box";
  }
};

#endif // GAME_BOX_EXCEPTIONS_HPP
