#include <iostream>
#include <vector>
#include <functional>


int doubleANumber( int aNumber )
{
    return aNumber * 2;
}


int addThreeNumbers( int aFirst, int aSecond, int aThird )
{
    return aFirst + aSecond + aThird;
}


class Class
{
public:     static int DoubleANumber( int aNumber );
			int AddThreeNumbers(int aFirst, int aSecond, int aThird)
			{ 
				return aFirst + aSecond + aThird;
			};
            int doubleANumber( int aNumber );
};


Class c;
Class *pC;


int Class::DoubleANumber( int aNumber )
{
    return aNumber * 2;
}


int Class::doubleANumber( int aNumber )
{
    return aNumber * 2;
}


void demoFunctionPointer( void )
{
    std::cout << "Starting with classic function pointers" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    int( *func )( int aNumber );
    func = &doubleANumber;

    std::cout << "Doubling 33 with doubleANumber(): " << doubleANumber( 33 ) << std::endl;
    std::cout << "Doubling 33 with doubleANumber() assigned to func(): " << func( 33 ) << std::endl;

    func = &Class::DoubleANumber;

    std::cout << "Doubling 33 with Class::DoubleANumber() assigned to func(): " << func( 33 ) << std::endl;

    int( Class::*mFunc )( int aNumber );

    Class c;

    mFunc = &Class::doubleANumber;

    std::cout << "Doubling 33 with Class::doubleANumber() using a stack allocated instance: " << ( c.*mFunc )( 33 ) << std::endl;

    Class *pC = new Class();

    std::cout << "Doubling 33 with Class::doubleANumber() using a heap allocated instance: " << ( ( *pC ).*mFunc )( 33 ) << std::endl;
}


void demoStdFunction( void )
{
    std::cout << "Starting with std::function" << std::endl;
    std::cout << "---------------------------" << std::endl;

    std::function<int( int )> stdFunc;

    stdFunc = doubleANumber;

    std::cout << "Doubling 33 with doubleANumber() assigned to stdFunc: " << stdFunc( 33 ) << std::endl;

    stdFunc = Class::DoubleANumber;

    std::cout << "Doubling 33 with Class::DoubleANumber() assigned to stdFunc: " << stdFunc( 33 ) << std::endl;

    stdFunc = []( int aNumber ) { return aNumber * 2; };

    std::cout << "Doubling 33 with lambda function assigned to stdFunc: " << stdFunc( 33 ) << std::endl;

    std::function<int( Class&, int )> stdMFunc;
	std::function<int( Class*&, int)> stdMtestFunc;

    stdMFunc = std::mem_fn( &Class::doubleANumber );
	stdMtestFunc = std::mem_fn(&Class::doubleANumber);

    std::cout << "Doubling 33 with Class::doubleANumber() assigned to stdMFunc using stack allocated instance: " << stdMFunc( c, 33 ) << std::endl;
    std::cout << "Doubling 33 with Class::doubleANumber() assigned to stdMFunc using heap allocated instance: " << stdMtestFunc( pC, 33 ) << std::endl;
}


void demoStdBind( void )
{
    std::cout << "Starting with std::bind" << std::endl;
    std::cout << "-----------------------" << std::endl;

    std::function<int(void)> boundFunc = std::bind( doubleANumber, 33 );

    std::cout << "Doubling 33 using canned call to doubleANumber( 33 ) stored in stdFunc: " << boundFunc() << std::endl;

    using std::placeholders::_1;

    std::function<int( int )> boundFunc2 = std::bind( addThreeNumbers, 11, 22, _1 );

    std::cout << "Adding 11, 22 and 33 using half-canned call to addThreeNumbers( 11, 22, _1 ) stored in boundFunc2: " << boundFunc2( 33 ) << std::endl;
}


void demoStdBindAndFunction( void )
{
    std::cout << "Starting with std::bind and std::function" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    std::function<int( int )> stdFunc;

    using std::placeholders::_1;
	using std::placeholders::_2;

    stdFunc = std::bind( &Class::doubleANumber, c, _1 );

	std::function<int(int, int)> OtherFunction = std::bind(&Class::AddThreeNumbers, c, _1, 2, _2);

    std::cout << "Doubling 33 using Class::doubleANumber() bound to instance." << stdFunc( 33 ) << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << OtherFunction(1, 1) << std::endl; 
	std::cout << std::endl;
	std::cout << std::endl;
}

int main( const int /*argc*/, const char * /*argv*/[] )
{
    pC = new Class();

    demoFunctionPointer();
    std::cout << std::endl;
    demoStdFunction();
    std::cout << std::endl;
    demoStdBind();
    std::cout << std::endl;
    demoStdBindAndFunction();
    std::cout << std::endl;

    system( "PAUSE" );

    delete pC;
    
    return 0;
}
