/***
 * File:   MemoryManager.h - Header File
 *         -----------------------------------------------------
 * Author: Peter Dalton
 * Date:   3/23/01 1:15:27 PM
 *
 * Description:
			This Memory Manager software provides the following functionality:
			  1. Seamless interface.
			  2. Tracking all memory allocations and deallocations.
				3. Reporting memory leaks, unallocated memory.
				4. Reporting memory bounds violations.
				5. Reporting the percentage of allocated memory that is actually being used.
				6. Customizable tracking.

	    The code is self documented, thus reading through this header file should tell you
			everything that you would ever need to know inorder to use the memory manager. 
 *
 * Copyright (C) Peter Dalton, 2001. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied warranties. You may freely copy 
 * and compile this source into applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 *                  "Portions Copyright (C) Peter Dalton, 2001"
 */

#ifndef _MEMORYMANAGER_H__
#define _MEMORYMANAGER_H__   

#ifdef _DEBUG 
#define ACTIVATE_MEMORY_MANAGER
#endif

#define ACTIVATE_MEMORY_MANAGER

#include "new_off.h"          // Make sure that the new/delete are not declared to avoid
                              //  circular definitions.

#include <stdlib.h>           // Required for malloc() and free()

// Only activate the memory manager if the flag has been defined.  This allows for the 
// performance hit to be avoided if desired.
#ifdef ACTIVATE_MEMORY_MANAGER

/*******************************************************************************************/
// ***** User interface, these methods can be used to set parameters within the Memory 
// ***** Manager to control the type and extent of the memory tests that are performed.  Note 
// ***** that it is not necessary to call any of these methods, you will get the default 
// ***** Memory Manager automatically.

void dumpLogReport( void );          
void dumpMemoryAllocations( void );  
void setLogFile( char *file ); 
void setExhaustiveTesting( bool test = true );
void setLogAlways( bool log = true );
void setPaddingSize( int size = 4 );
void cleanLogFile( bool clean = true );
void breakOnAllocation( int allocationCount );
void breakOnDeallocation( void *address ); 
void breakOnReallocation( void *address );

/*******************************************************************************************/
// ***** Memory Manager specific definitions.  Below are the definitions that make up the 
// ***** Memory Manager.
 
// Posible allocation/deallocation types.  
typedef char ALLOC_TYPE;
const ALLOC_TYPE MM_UNKNOWN        = 0;  // Declared as characters to minimize memory footprint, 
const ALLOC_TYPE MM_NEW            = 1;  //   char = 1 byte
const ALLOC_TYPE MM_NEW_ARRAY      = 2;  //   enum types = int = 32 bits = 8 bytes on standard machines
const ALLOC_TYPE MM_MALLOC         = 3;
const ALLOC_TYPE MM_CALLOC         = 4;
const ALLOC_TYPE MM_REALLOC        = 5;
const ALLOC_TYPE MM_DELETE         = 6;
const ALLOC_TYPE MM_DELETE_ARRAY   = 7;
const ALLOC_TYPE MM_FREE           = 8;

void *AllocateMemory( const char *file, int line, size_t size, ALLOC_TYPE type, void *address = NULL );
void deAllocateMemory( void *address, ALLOC_TYPE type );
void setOwner( const char *file, int line );

/*******************************************************************************************/
// ***** Here we define a static class that will be responsible for initializing the Memory
// ***** Manager.  It is critical that it is placed here within the header file to ensure
// ***** that this static object will be created before any other static objects are 
// ***** intialized.  This will ensure that the Memory Manager is alive when other static
// ***** objects allocate and deallocate memory.  Note that static objects are deallocated
// ***** in the reverse order in which they are allocated, thus this class will be 
// ***** deallocated last.

class Initialize { public: Initialize(); };
static Initialize InitMemoryManager;

/*******************************************************************************************/
// ***** Global overloaded new/delete operators

// ***** These two routines should never get called, however they are provided here for 
// ***** clarity and to through.
inline void* operator new( size_t size )    { return malloc( size ); }
inline void* operator new[]( size_t size )  { return malloc( size ); }

inline void* operator new( size_t size, const char *file, int line ) 
{
  return AllocateMemory( file, line, size, MM_NEW ); 
}

inline void* operator new[]( size_t size, const char *file, int line ) {return AllocateMemory( file, line, size, MM_NEW_ARRAY );}
inline void operator delete( void *address )
{
  if (!address) return;  // ANSI states that delete will allow NULL pointers.
	deAllocateMemory( address, MM_DELETE );
}

inline void operator delete[]( void *address )
{
  if (!address) return;  // ANSI states that delete will allow NULL pointers.
	deAllocateMemory( address, MM_DELETE_ARRAY );
}

// ***** These two routines should never get called, unless an error occures during the 
// ***** allocation process.  These need to be defined to make Visual C++ 6.0 happy.
// ***** If there was an allocation problem these method would be called automatically by 
// ***** the operating system.  C/C++ Users Journal (Vol. 19 No. 4 -> April 2001 pg. 60)  
// ***** has an excellent explanation of what is going on here.
inline void operator delete( void *address, const char *file, int line )   { free( address ); }
inline void operator delete[]( void *address, const char *file, int line ) { free( address ); }

#include "new_on.h"
#endif /* ACTIVATE_MEMORY_MANAGER */
#endif /* _MEMORYMANAGER_H__ */