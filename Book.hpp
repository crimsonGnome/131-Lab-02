#pragma once                                                    // include guard

#include <compare>                                              // std::weak_ordering
#include <iostream>
#include <string>




class Book
{
  // Insertion and Extraction Operators
  friend std::ostream & operator<<( std::ostream & stream, Book const & book );
  friend std::istream & operator>>( std::istream & stream, Book       & book );

  public:
    // Constructors, assignments, and destructor
    Book( std::string title  = {},                              // Default and Conversion (from string to Book) constructor
          std::string author = {},
          std::string isbn   = {},
          double      price  = 0.0 );

    Book & operator=( Book const  & rhs   ) &;                  // Assignment operators available only for l-values, and then
    Book & operator=( Book       && rhs   ) & noexcept;         // the 'Rule of 5' says if you define one, then you should define them all
    Book            ( Book const  & other );                    // OK:  Book a{"title"},b;  b = a;  (a and b are both l-values, i.e. named objects)
    Book            ( Book       && other )   noexcept;         // Error:  Book{} = a;              (Book{} is an r-value, i.e., an unnamed temporary object)
   ~Book            (                     )   noexcept;


    // Accessors
    std::string const & isbn  () const &;                       // Returns object's state by constant reference for l-values
    std::string const & title () const &;                       // (The & at the end says these functions can be called only for l-values)
    std::string const & author() const &;
    double              price () const &;

    std::string isbn  () &&;                                    // Returns object's state by value for r-values (unsafe to return by reference)
    std::string title () &&;                                    // (The && at the end says these functions can be called only for r-values)
    std::string author() &&;

    // Modifiers                                                // Updates object's state and returns a reference to self (enables chaining)
    Book & isbn  ( std::string newIsbn   ) &;
    Book & title ( std::string newTitle  ) &;                   // Mutators available for l-values only   (The & at the end says these functions can be called only for l-values)
    Book & author( std::string newAuthor ) &;                   // OK:     Book b; b.price(13.99);        (b is an l-value, i.e. a named object)
    Book & price ( double      newPrice  ) &;                   // Error:  Book{}.price(13.99);           (Book{} is an r-value, i.e., an unnamed temporary object)


    // Relational Operators
    std::weak_ordering operator<=>( Book const & rhs ) const noexcept;
    bool               operator== ( Book const & rhs ) const noexcept;

  private:
    std::string _isbn;                                          // a 10 or 13 character international standard book number uniquely identifying this book (Ex: 9790619213090,  979010181X).
    std::string _title;                                         // the name of the book (Ex: An Introduction to Programming with C++,  Data structures for particle physics experiments)
    std::string _author;                                        // the book's author (Ex: Diane Zak,  Alison "Ally" Uttley)
    double      _price = 0.0;                                   // the cost of the book in US Dollars (Ex:  74.99,  115.50)
};
