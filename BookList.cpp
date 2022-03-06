#include <algorithm>                              // find(), move(), move_backward(), equal(), swap(), lexicographical_compare()
#include <cmath>                                  // min()
#include <cstddef>                                // size_t
#include <initializer_list>
#include <iomanip>                                // setw()
#include <iterator>                               // distance(), next()
#include <stdexcept>                              // logic_error
#include <string>

#include "Book.hpp"
#include "BookList.hpp"



// As a rule, I strongly recommend avoiding macros, unless there is a compelling reason - this is such a case. This really does need
// to be a macro and not a function due to the way the preprocessor expands the source code location information.  It's important to
// have these expanded where they are used, and not here. But I just can't bring myself to writing this, and getting it correct,
// everywhere it is used.  Note:  C++20 will change this technique with the introduction of the source_location class. Also note the
// usage of having the preprocessor concatenate two string literals separated only by whitespace.
#define exception_location "\n detected in function \"" + std::string(__func__) +  "\""    \
                           "\n at line " + std::to_string( __LINE__ ) +                    \
                           "\n in file \"" __FILE__ "\""












///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Initializer List Constructor
BookList::BookList( const std::initializer_list<Book> & initList )
{
  for( auto && book : initList )   insert( book, Position::BOTTOM );

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
}












///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Queries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// size() const
std::size_t BookList::size() const
{
  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  ///////////////////////// TO-DO (1) //////////////////////////////
    /// All the containers are the same size, so pick one and return the size of that.  Since the forward_list has to calculate the
    /// size on demand, stay away from using that one.

  /////////////////////// END-TO-DO (1) ////////////////////////////
}












///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Accessors
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// find() const
std::size_t BookList::find( const Book & book ) const
{
  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  ///////////////////////// TO-DO (2) //////////////////////////////
    /// Locate the book in this book list and return the zero-based position of that book.  If the book does not exist, return the
    /// size of this book list as an indicator the book does not exist.  The book will be in the same position in all the containers
    /// (array, vector, list, and forward_list) so pick just one of those to search.  The STL provides the find() function that is a
    /// perfect fit here, but you may also write your own loop.

  /////////////////////// END-TO-DO (2) ////////////////////////////
}












///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Modifiers
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// insert( position )
void BookList::insert( const Book & book, Position position )
{
  // Convert the TOP and BOTTOM enumerations to an offset and delegate the work
  if     ( position == Position::TOP    )  insert( book, 0      );
  else if( position == Position::BOTTOM )  insert( book, size() );
  else                                     throw std::logic_error( "Unexpected insertion position" exception_location );  // Programmer error.  Should never hit this!
}



// insert( offset )
void BookList::insert( const Book & book, std::size_t offsetFromTop )       // insert new book at offsetFromTop, which places it before the current book at offsetFromTop
{
  // Validate offset parameter before attempting the insertion.  std::size_t is an unsigned type, so no need to check for negative
  // offsets, and an offset equal to the size of the list says to insert at the end (bottom) of the list.  Anything greater than the
  // current size is an error.
  if( offsetFromTop > size() )   throw InvalidOffset_Ex( "Insertion position beyond end of current list size" exception_location );


  /**********  Prevent duplicate entries  ***********************/
  ///////////////////////// TO-DO (3) //////////////////////////////
    /// Silently discard duplicate items from getting added to the book list.  If the to-be-inserted book is already in the list,
    /// simply return.
    ///
    /// Remember, you already have a function that tells you if the to-be-inserted book is already in the list, so use it.  Don't
    /// implement it again.

  /////////////////////// END-TO-DO (3) ////////////////////////////

    
  // Inserting into the book list means you insert the book into each of the containers (array, vector, list, and forward_list).
  // Because the data structure concept is different for each container, the way a book gets inserted is a little different for
  // each.  You are to insert the book into each container such that the ordering of all the containers is the same.  A check is
  // made at the end of this function to verify the contents of all four containers are indeed the same.

  
  { /**********  Part 1 - Insert into array  ***********************/
    ///////////////////////// TO-DO (4) //////////////////////////////
      /// Hint:  "Vector.hpp" in our Sequence Container Implementation Examples shows you how to do this.  (wink wink)
      ///
      ///
      /// Unlike the other containers, std::array has no insert() function, so you have to write it yourself. Insert into the array
      /// by shifting all the items at and after the insertion point (offsetFromTop) to the right opening a gap in the array that
      /// can be populated with the given book.  Remember that arrays have fixed capacity and cannot grow, so make sure there is
      /// room in the array for another book before you start by verifying _books_array_size is less than _books_array.size().  If
      /// not, throw CapacityExceeded_ex.  Also remember that you must keep track of the number of valid books in your array, so
      /// don't forget to adjust _books_array_size.
      ///
      /// Open a hole to insert new book by shifting to the right everything at and after the insertion point.
      /// For example:  a[8] = a[7];  a[7] = a[6];  a[6] = a[5];  and so on.
      /// std::move_backward will be helpful, or write your own loop.

    /////////////////////// END-TO-DO (4) ////////////////////////////
  } // Part 1 - Insert into array



  
  { /**********  Part 2 - Insert into vector  **********************/
    ///////////////////////// TO-DO (5) //////////////////////////////
      /// The vector STL container std::vector has an insert function, which can be directly used here.  But that function takes a
      /// pointer (or more accurately, an iterator) that points to the book to insert before.  You need to convert the zero-based
      /// offset from the top (the index) to an iterator by advancing _books_vector.begin() offsetFromTop times.  The STL has a
      /// function called std::next() that does that, or you can use simple pointer arithmetic to calculate it.  "Vector.hpp" in our
      /// Sequence Container Implementation Examples also shows you how convert index to iterator, and iterator to index.
      ///
      /// Behind the scenes, std::vector::insert() shifts to the right everything at and after the insertion point, just like you
      /// did for the array above.

    /////////////////////// END-TO-DO (5) ////////////////////////////
  } // Part 2 - Insert into vector



  
  { /**********  Part 3 - Insert into doubly linked list  **********/
    ///////////////////////// TO-DO (6) //////////////////////////////
      /// The doubly linked list STL container std::list has an insert function, which can be directly used here.  But that function
      /// takes a pointer (or more accurately, an iterator) that points to the book to insert before.  You need to convert the
      /// zero-based offset from the top (the index) to an iterator by advancing _books_dl_list.begin() offsetFromTop times.  The
      /// STL has a function called std::next() that does that, or you can write your own loop.

    /////////////////////// END-TO-DO (6) ////////////////////////////
  } // Part 3 - Insert into doubly linked list



  
  { /**********  Part 4 - Insert into singly linked list  **********/
    ///////////////////////// TO-DO (7) //////////////////////////////
      /// The singly linked list STL container std::forward_list has an insert function, which can be directly used here.  But that
      /// function inserts AFTER the book pointed to, not before like the other containers.  A singly linked list cannot look
      /// backwards, only forward.  You need to convert the zero-based offset from the top (the index) to an iterator by advancing
      /// _books_sl_list.before_begin() offsetFromTop times.  The STL has a function called std::next() that does that, or you can
      /// write your own loop.

    /////////////////////// END-TO-DO (7) ////////////////////////////
  } // Part 4 - Insert into singly linked list


  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
} // insert( const Book & book, std::size_t offsetFromTop )



// remove( book )
void BookList::remove( const Book & book )
{
  // Delegate to the version of remove() that takes an index as a parameter
  remove( find( book ) );
}



// remove( offset )
void BookList::remove( std::size_t offsetFromTop )
{
  // Removing from the book list means you remove the book from each of the containers (array, vector, list, and forward_list).
  // Because the data structure concept is different for each container, the way an book gets removed is a little different for
  // each.  You are to remove the book from each container such that the ordering of all the containers is the same.  A check is
  // made at the end of this function to verify the contents of all four containers are indeed the same.

  if( offsetFromTop >= size() )   return;                                          // no change occurs if (zero-based) offsetFromTop >= size()

  
  { /**********  Part 1 - Remove from array  ***********************/
    ///////////////////////// TO-DO (8) //////////////////////////////
      /// Hint:  "Vector.hpp" in our Sequence Container Implementation Examples shows you how to do this.  (wink wink)
      ///
      ///
      /// Close the hole created by shifting to the left everything at and after the remove point.
      /// For example:  a[5] = a[6];  a[6] = a[7];  a[7] = a[8];  and so on
      ///
      /// std::move() will be helpful, or write your own loop.  Also remember that you must keep track of the number of valid books
      /// in your array, so don't forget to adjust _books_array_size.

    /////////////////////// END-TO-DO (8) ////////////////////////////
  } // Part 1 - Remove from array



  
  { /**********  Part 2 - Remove from vector  **********************/
    ///////////////////////// TO-DO (9) //////////////////////////////
      /// The vector STL container std::vector has an erase function, which can be directly used here.  But that function takes a
      /// pointer (or more accurately, an iterator) that points to the book to be removed.  You need to convert the zero-based
      /// offset from the top (the index) to an iterator by advancing _books_vector.begin() offsetFromTop times.  The STL has a
      /// function called std::next() that does that, or you can use simple pointer arithmetic to calculate it.  "Vector.hpp" in our
      /// Sequence Container Implementation Examples also shows you how convert index to iterator, and iterator to index.
      ///
      /// Behind the scenes, std::vector::erase() shifts to the left everything after the insertion point, just like you did for the
      /// array above.

    /////////////////////// END-TO-DO (9) ////////////////////////////
  } // Part 2 - Remove from vector



  
  { /**********  Part 3 - Remove from doubly linked list  **********/
    ///////////////////////// TO-DO (10) //////////////////////////////
      /// The doubly linked list STL container std::list has an erase function, which can be directly used here.  But that function
      /// takes a pointer (or more accurately, an iterator) that points to the book to remove.  You need to convert the zero-based
      /// offset from the top (the index) to an iterator by advancing _books_dl_list.begin() offsetFromTop times.  The STL has a function called
      /// std::next() that does that, or you can write your own loop.

    /////////////////////// END-TO-DO (10) ////////////////////////////
  } // Part 3 - Remove from doubly linked list



  
  {/**********  Part 4 - Remove from singly linked list  **********/
    ///////////////////////// TO-DO (11) //////////////////////////////
      /// The singly linked list STL container std::forward_list has an erase function, which can be directly used here.  But that
      /// function erases AFTER the book pointed to, not the one pointed to like the other containers.  A singly linked list cannot
      /// look backwards, only forward.  You need to convert the zero-based offset from the top (the index) to an iterator by
      /// advancing _books_sl_list.before_begin() offsetFromTop times.  The STL has a function called std::next() that does that, or
      /// you can write your own loop.

    /////////////////////// END-TO-DO (11) ////////////////////////////
  } // Part 4 - Remove from singly linked list


  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
} // remove( std::size_t offsetFromTop )



// moveToTop()
void BookList::moveToTop( const Book & book )
{
  ///////////////////////// TO-DO (12) //////////////////////////////
    /// If the book exists, then remove and reinsert it.  Otherwise, do nothing.
    ///
    /// Remember, you already have functions to do all this.  Use BookList::find() to determine if the book
    /// exists in this book list, and then remove() and insert() to reposition the book.

  /////////////////////// END-TO-DO (12) ////////////////////////////
}



// operator+=( initializer_list )
BookList & BookList::operator+=( const std::initializer_list<Book> & rhs )
{
  ///////////////////////// TO-DO (13) //////////////////////////////
    /// Concatenate the right hand side to the bottom of this list by repeatedly inserting at the bottom of this book list. The
    /// input type is a container of books accessible with iterators like all the other containers.  The constructor above gives an
    /// example.  Just like the above example, use BookList::insert() to insert each book of rhs at the bottom of this list.

  /////////////////////// END-TO-DO (13) ////////////////////////////

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
  return *this;
}



// operator+=( Booklist )
BookList & BookList::operator+=( const BookList & rhs )
{
  ///////////////////////// TO-DO (14) //////////////////////////////
    /// Concatenate the right hand side to the bottom of this list by repeatedly inserting at the bottom of this book list. All the
    /// rhs containers (array, vector, list, and forward_list) contain the same information, so pick just one to traverse. Walk the
    /// container you picked inserting its books to the bottom of this book list. Use BookList::insert() to insert at the bottom.

  /////////////////////// END-TO-DO (14) ////////////////////////////

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
  return *this;
}












///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Relational Operators
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// operator<=>
std::weak_ordering BookList::operator<=>( BookList const & rhs ) const
{
  if( !containersAreConsistant() || !rhs.containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  ///////////////////////// TO-DO (15) //////////////////////////////
    /// Find the common extent.  That is, if one list has 20 books, and the other has only 13, then the common extent is 13 books.
    /// We can compare only the first 13 books of each list.  Find the first book in the common extent that is different using
    /// three-way comparison (e.g., b1 <=> b2  !=  0) and return the results.  If no differences were found in the common extent,
    /// then the list with the smaller size is less than the other.  In that case, return the results of three-way comparing the
    /// sizes.
    ///
    ///
    /// The content of all the book lists's containers is the same - so pick an easy one to walk.

  /////////////////////// END-TO-DO (15) ////////////////////////////
}



// operator==
bool BookList::operator==( BookList const & rhs ) const
{
  if( !containersAreConsistant() || !rhs.containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  ///////////////////////// TO-DO (16) //////////////////////////////
    /// Two lists are different if their sizes are different, or one of their books is different.  Otherwise the lists are equal.
    /// Comparing the sizes is quick (constant time), so check that first.
    ///
    ///
    /// The content of all the book lists's containers is the same - so pick an easy one to walk.

  /////////////////////// END-TO-DO (16) ////////////////////////////
}












///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private member functions
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// containersAreConsistant() const
bool BookList::containersAreConsistant() const
{
  // Sizes of all containers must be equal to each other
  if(    _books_array_size != _books_vector.size()
      || _books_array_size != _books_dl_list.size()
      || _books_array_size !=  books_sl_list_size() ) return false;

  // Element content and order must be equal to each other
  auto current_array_position   = _books_array  .cbegin();
  auto current_vector_position  = _books_vector .cbegin();
  auto current_dl_list_position = _books_dl_list.cbegin();
  auto current_sl_list_position = _books_sl_list.cbegin();

  auto end = _books_vector.cend();
  while( current_vector_position != end )
  {
    if(    *current_array_position != *current_vector_position
        || *current_array_position != *current_dl_list_position
        || *current_array_position != *current_sl_list_position ) return false;

    // Advance the iterators to the next element in unison
    ++current_array_position;
    ++current_vector_position;
    ++current_dl_list_position;
    ++current_sl_list_position;
  }

  return true;
}



// books_sl_list_size() const
std::size_t BookList::books_sl_list_size() const
{
  ///////////////////////// TO-DO (17) //////////////////////////////
    /// Some implementations of a singly linked list maintain the size (number of elements in the list).  std::forward_list does
    /// not. The size of singly linked list must be calculated on demand by walking the list from beginning to end counting the
    /// number of elements visited.  The STL's std::distance() function does that, or you can write your own loop.

  /////////////////////// END-TO-DO (17) ////////////////////////////
}












///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Non-member functions
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// operator<<
std::ostream & operator<<( std::ostream & stream, const BookList & bookList )
{
  if( !bookList.containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  unsigned count = 0;
  for( auto && book : bookList._books_sl_list )   stream << '\n' << std::setw(5) << count++ << ":  " << book;

  return stream;
}



// operator>>
std::istream & operator>>( std::istream & stream, BookList & bookList )
{
  if( !bookList.containersAreConsistant() )   throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  for( Book book; stream >> book; )   bookList.insert( book, BookList::Position::BOTTOM );

  return stream;
}
