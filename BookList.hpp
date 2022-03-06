#pragma once                                                                                  // include guard

#include <array>
#include <compare>                                                                            // weak_ordering
#include <cstddef>                                                                            // size_t
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <list>
#include <stdexcept>                                                                          // domain_error, length_error, logic_error
#include <vector>

#include "Book.hpp"


class BookList
{
  // Insertion and Extraction Operators
  friend std::ostream & operator<<( std::ostream & stream, BookList const & bookList );
  friend std::istream & operator>>( std::istream & stream, BookList       & bookList );

  public:
    // Types and Exceptions
    enum class Position {TOP, BOTTOM};

    struct InvalidInternalState_Ex : std::domain_error { using domain_error::domain_error; }; // Thrown if internal data structures become inconsistent with each other
    struct CapacityExceeded_Ex     : std::length_error { using length_error::length_error; }; // Thrown if more books are inserted than will fit
    struct InvalidOffset_Ex        : std::logic_error  { using logic_error ::logic_error;  }; // Thrown if inserting beyond current size


    // Constructors, destructor, and assignments
    //
    // The compiler synthesized copy and move constructors, and copy and move assignment operators work just fine.  But since I also
    // have user defined constructors, I need to explicitly say the compiler synthesized default constructor is also okay.
    BookList() = default;                                                                     // constructs an empty book list
    BookList( std::initializer_list<Book> const & initList );                                 // constructs a book list from a braced list of books


    // Queries
    std::size_t size() const;                                                                 // returns the number of books in this book list


    // Accessors
    std::size_t find( const Book & book ) const;                                              // returns the (zero-based) offset from top of list
                                                                                              // returns the (zero-based) position of the book, size() if book not found

    // Modifiers
    void insert( Book const & book, Position    position = Position::TOP );                   // add the book to the top (beginning) or bottom (end) of the book list
    void insert( Book const & book, std::size_t offsetFromTop            );                   // inserts before the existing book currently at that offset

    void remove( Book const  & book          );                                               // no change occurs if book not found
    void remove( std::size_t   offsetFromTop );                                               // no change occurs if (zero-based) offsetFromTop >= size()

    void moveToTop( Book const & book );                                                      // finds then moves book from its current position to the top of the book list

    BookList & operator+=( std::initializer_list<Book> const & rhs );                         // concatenates a braced list of books to the end of this list
    BookList & operator+=( BookList                    const & rhs );                         // concatenates the rhs list to the end of this list


    // Relational Operators
    std::weak_ordering operator<=>( BookList const & rhs ) const;
    bool               operator== ( BookList const & rhs ) const;


  private:
    // Instance Attributes
    std::size_t             _books_array_size = 0;                                            // std::array's size is constant so manage that attributes ourself
    std::array<Book, 11>    _books_array;
    std::vector<Book>       _books_vector;
    std::list<Book>         _books_dl_list;
    std::forward_list<Book> _books_sl_list;


    // Helper functions
    bool        containersAreConsistant() const;
    std::size_t books_sl_list_size     () const;                                              // std::forward_list doesn't maintain size, so calculate it on demand
};
