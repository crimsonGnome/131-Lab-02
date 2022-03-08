#include <exception>
#include <iostream>
#include <typeinfo>

#include "Book.hpp"
#include "BookList.hpp"




namespace
{
  void basicScenario()
  {
    // Let's start a book list
    BookList booksToRead = {{"Inviable Man"           },
                            {"Moby Dick"              },
                            {"Les Mis"                },
                            {"A Tale of Two Cities"   }};

    // Changed my mind, I want to make sure I read Les Mis first so I'm going to move that to the top of my list
    booksToRead.moveToTop( {"Les Mis"} );

    // Let's see what's on the list so far
    std::cout << "My Book List" << booksToRead << "\n\n";

    // Yay, no.  Need to add a few more
    booksToRead += {{"Ulysses"          },
                    {"The Color Purple" }};


    // My roommate also has a book list
    BookList roommatesList = {{"Hunger Games", "S. Collins"               },
                              {"Hunger Games", "Suzanne Collins"          },
                              {"Les Mis"                                  },
                              {"Secret Garden", "Frances Hodgson Burnett" },
                              {"Charlie & Choc Factory"                   }};

    std::cout << "My roommate's Book List" << roommatesList << "\n\n";

    // Let's combine the lists (if different) and go shopping
    if( booksToRead != roommatesList ) booksToRead += roommatesList;


    // Oops, forgot one of my favorites.  Let's add that right before '2 cities.
    booksToRead.insert( {"Oliver Twist", "Charles Dickens"}, booksToRead.find( {"A Tale of Two Cities"} ) );

    // Time is short, let me take one off the list!
    booksToRead.remove( {"Secret Garden", "Frances Hodgson Burnett"} );


    // Now let's see what's on the list
    std::cout << "Combined Book Lists" << booksToRead << "\n\n";



    // Did you get it right?
    BookList expectedResults = {{"Les Mis"                         },
                                {"Inviable Man"                    },
                                {"Moby Dick"                       },
                                {"Oliver Twist", "Charles Dickens" },
                                {"A Tale of Two Cities"            },
                                {"Ulysses"                         },
                                {"The Color Purple"                },
                                {"Hunger Games", "S. Collins"      },
                                {"Hunger Games", "Suzanne Collins" },
                                {"Charlie & Choc Factory"          }};

    std::cout << "\nExpected results:" << expectedResults                                        << "\n\n"
              << "\nActual results:"   << booksToRead                                            << "\n\n"
              << "\nTest results:  "   << ( booksToRead == expectedResults  ? "PASS"  :  "FAIL") << '\n';
  }
}




int main()
{
  try
  {
    basicScenario();


    ///////////////////////// TO-DO (1) //////////////////////////////
     /// Create, manipulate, and display your own BookList object here.  Not looking for anything specific but don't just repeat
     /// what I've already done above.  Be imaginative and create your own story.  Try to use all the functions of the BookList
     /// interface, including the insertion, extraction, and relational operators.  Try inserting books from both the top and the
     /// bottom of the lists.  Remove books from the top, middle, and bottom.  Create, concatenate, rearrange, and compare several
     /// lists.  Have some fun with it!  The purpose is to show me you as a client understand how to *use* the BookList.
    // Let's start a book list

    // Crate Book list 
    BookList booksInMyLibrary = {{"Jurrasic Park"},
                            {"The Prine's Milk"},
                            {"Xenocide"},
                            {"The Fellowship of the Ring"}};

    // Let's see what's on the list so far
    std::cout << "\n\nCrimsonGnome's Book List" << booksInMyLibrary << "\n\n";

    // Move Book to the top of the list
    booksInMyLibrary.moveToTop( {"The Prine's Milk"} );

    // Yay, no.  Need to add a few more
    booksInMyLibrary += {{"The Pragmatic Programmer"},
                    {"The Ultimate Hitch Hiker's Guide to the Galaxy"},
                    {"Eragon" }};

                    
    // Getting rid of some books to make some space
    booksInMyLibrary.remove( {"Xenocide"} );
    booksInMyLibrary.remove( {"Jurrasic Park"} );

    // My roommate also has a book list
    BookList babyBooks = {{"First 100 words"},
                              {"Goodnight Moon"},
                              {"Love You Forever"},
                              {"On my Leaf" },
                              {"The Cat in the Hat"}};

    std::cout << "Aurelia's Book List" << babyBooks << "\n\n";

    // Let's combine the lists (if different) and go shopping
    if( booksInMyLibrary != babyBooks ) booksInMyLibrary += babyBooks;

    // Mix up books because thats how life works 
    booksInMyLibrary.moveToTop({"Goodnight Moon"});
    booksInMyLibrary.moveToTop({"The Ultimate Hitch Hiker's Guide to the Galaxy"});
    booksInMyLibrary.moveToTop({"The Cat in the Hat"});

    // Getting rid of some books to make some space
    booksInMyLibrary.remove( {"On my Leaf"} );

    // Need to have this one
    booksInMyLibrary.insert( {"The Bible"}, booksInMyLibrary.find( {"The Pragmatic Programmer"} ) );
    
    // Combined book list
    std::cout << "Family Book Lists" << booksInMyLibrary << "\n\n";

  
    /////////////////////// END-TO-DO (1) ////////////////////////////
  }

  catch( const std::exception & ex )
  {
    std::cerr << "Fatal Error:  unhanded exception \"" << typeid( ex ).name() << "\"\n"
              << ex.what() << '\n';
  }
}
