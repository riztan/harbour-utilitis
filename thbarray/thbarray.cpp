//-----------------------------------------------------------------------------
// Clase THbArray
// Autor: Manu Expósito
//-----------------------------------------------------------------------------

#include "thbarray.h"
#include "hbinit.h"

//-----------------------------------------------------------------------------

#define _GETOBJC0() static_cast<THbArray *>(THbArray::getObjC())
#define _GETOBJC1(pxObj) static_cast<THbArray *>(THbArray::getObjC((pxObj)))

//-----------------------------------------------------------------------------
// Declaracion de funciones estaticas

static void THBARRAY_NEW( void );
static void THBARRAY_ADD( void );
static void THBARRAY_INS( void );
static void THBARRAY_SET( void );
static void THBARRAY_DEL( void );
static void THBARRAY_GOTO( void );
static void THBARRAY_GOTOP( void );
static void THBARRAY_GOBOTTOM( void );
static void THBARRAY_NEXT( void );
static void THBARRAY_PRIOR( void );
static void THBARRAY_SKIP( void );
static void THBARRAY_RECNO( void );
static void THBARRAY_BOF( void );
static void THBARRAY_EOF( void );
static void THBARRAY_LEN( void );
static void THBARRAY_SKIPPER( void );
static void THBARRAY_VALUE( void );
static void THBARRAY_CURRENT( void );
static void THBARRAY_FREE( void );

//-----------------------------------------------------------------------------
// Metodos de la clase THbArray (C++)
//-----------------------------------------------------------------------------

// Constructor de la clase.
THbArray::THbArray( void )
{
	FArray = hb_itemNew( nullptr );
}

// Destructor de la clase.
THbArray::~THbArray( void )
{
	if( FArray != nullptr )
	{
		hb_gcGripDrop( FArray );
		FArray = nullptr;
	}
}
// Lista de Metodos xBase
void THbArray::addMethods( HB_USHORT usClassH ) const
{
	// Estilo xBase:
	hb_clsAdd( usClassH, "NEW", THBARRAY_NEW );
	hb_clsAdd( usClassH, "ADD", THBARRAY_ADD );
	hb_clsAdd( usClassH, "INSERT", THBARRAY_INS );
	hb_clsAdd( usClassH, "SET", THBARRAY_SET );
	hb_clsAdd( usClassH, "DELETE", THBARRAY_DEL );
	hb_clsAdd( usClassH, "GOTO", THBARRAY_GOTO );
	hb_clsAdd( usClassH, "SKIP", THBARRAY_SKIP );
	hb_clsAdd( usClassH, "BOF", THBARRAY_BOF );
	hb_clsAdd( usClassH, "EOF", THBARRAY_EOF );
	hb_clsAdd( usClassH, "GOTOP", THBARRAY_GOTOP );
	hb_clsAdd( usClassH, "GOBOTTOM", THBARRAY_GOBOTTOM );
	hb_clsAdd( usClassH, "RECNO", THBARRAY_RECNO );
	hb_clsAdd( usClassH, "LEN", THBARRAY_LEN );
	hb_clsAdd( usClassH, "FREE", THBARRAY_FREE );
	// Estilo nuevo:
	hb_clsAdd( usClassH, "APPEND", THBARRAY_ADD );	// append => add
	hb_clsAdd( usClassH, "INSERT", THBARRAY_INS );	// insert => ins
	hb_clsAdd( usClassH, "UPDATE", THBARRAY_SET );	// update => set
	hb_clsAdd( usClassH, "DELETE", THBARRAY_DEL );	// delete => del
	hb_clsAdd( usClassH, "MOVEBY", THBARRAY_SKIP );	// moveBy => skip
	hb_clsAdd( usClassH, "FIRST", THBARRAY_GOTOP );	// first => goTop
	hb_clsAdd( usClassH, "LAST", THBARRAY_GOBOTTOM );	// last => goBottom
	hb_clsAdd( usClassH, "NEXT", THBARRAY_NEXT );	// next => skip( 1 )
	hb_clsAdd( usClassH, "PRIOR", THBARRAY_PRIOR );	// prior  => skip( -1 )
	hb_clsAdd( usClassH, "GETPOS", THBARRAY_RECNO );	// getPos => recNo
	hb_clsAdd( usClassH, "GETSIZE", THBARRAY_LEN );	// getSize => len
	hb_clsAdd( usClassH, "END", THBARRAY_FREE );	// free => end
	hb_clsAdd( usClassH, "VALUE", THBARRAY_VALUE );
	hb_clsAdd( usClassH, "CURRENT", THBARRAY_CURRENT );
	hb_clsAdd( usClassH, "SKIPPER", THBARRAY_SKIPPER );
}

// Constructor (new -> sin parametro). Inicializa las variables de instancia
void THbArray::init( void )
{
	hb_arrayNew( FArray, 0 );

	FPos = 0;
	bFirst = bLast = HB_TRUE;
}

// Constructor (new -> con parametro). Inicializa las variables de instancia
void THbArray::init( PHB_ITEM pArray )
{
	hb_arrayCloneTo( FArray, pArray );

	if( getSize() > 0 )
	{
		FPos = 1;
		bFirst = bLast = HB_FALSE;
	}
	else
	{
		FPos = 0;
		bFirst = bLast = HB_TRUE;
	}
}

HB_BOOL THbArray::append( PHB_ITEM pItem )
{
	return hb_arrayAdd( FArray, pItem );
}

HB_BOOL THbArray::insert( PHB_ITEM pItem )
{
	HB_BOOL bRet = hb_arrayIns( FArray, FPos );

	if( bRet )
	{
		bRet = hb_arraySet( FArray, FPos, pItem );
	}

	return bRet;
}

HB_BOOL THbArray::update( PHB_ITEM pItem )
{
	return hb_arraySet( FArray, FPos, pItem );
}

HB_BOOL THbArray::erase( void )
{
	HB_BOOL bRet = hb_arrayDel( FArray, FPos );

	if( bRet )
	{
		bRet = hb_arraySize( FArray, getSize() - 1 );
	}

	return bRet;
}

void THbArray::goTo( HB_SIZE nPos )
{
	HB_SIZE nSize = getSize();

	if( nPos > nSize )
	{
		FPos = nSize;
		bFirst = HB_FALSE;
		bLast = HB_TRUE;
	}
	else if( nPos < 1 )
	{
		FPos = 1;
		bFirst = HB_TRUE;
		bLast = HB_FALSE;
	}
	else
	{
		FPos = nPos;
		bFirst = bLast = HB_FALSE;
	}
}

void THbArray::skip( HB_ISIZ lPos )
{
	goTo( FPos + lPos );
}

HB_SIZE THbArray::getPos( void ) const
{
	return FPos;
}

PHB_ITEM THbArray::value( HB_SIZE nPos ) const
{
	return hb_arrayGetItemPtr( FArray, nPos );
}

PHB_ITEM THbArray::current( void ) const
{
	return value( FPos );
}

HB_SIZE THbArray::getSize( void ) const
{
	return hb_arrayLen( FArray );
}

HB_ISIZ THbArray::skipped( HB_ISIZ lSkip )
{
	HB_ISIZ lwSkip1 = 1 - FPos;
	HB_ISIZ lwSkip2 = getSize() - FPos;
	HB_ISIZ lSkipped = HB_MIN( HB_MAX( lSkip, lwSkip1 ), lwSkip2 );

	FPos += lSkipped;

	return lSkipped;
}

//-----------------------------------------------------------------------------
// Declaracion de funciones privadas. Metodos de THbArray (Hb)
// Normalmente wrappers de la clase de C++  TMyObject
//-----------------------------------------------------------------------------

static void THBARRAY_NEW( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();

	_GETOBJC1( pSelf )->init( hb_param( 1, HB_IT_ARRAY ) );

	hb_itemReturn( pSelf );
}

static void THBARRAY_ADD( void )
{
	hb_retl( _GETOBJC0()->append( hb_param( 1, HB_IT_ANY ) ) );
}

static void THBARRAY_INS( void )
{
	hb_retl( _GETOBJC0()->insert( hb_param( 1, HB_IT_ANY ) ) );
}

static void THBARRAY_SET( void )
{
	hb_retl( _GETOBJC0()->update( hb_param( 1, HB_IT_ANY ) ) );
}

static void THBARRAY_DEL( void )
{
	hb_retl( _GETOBJC0()->erase() );
}

static void THBARRAY_GOTO( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();

	_GETOBJC1( pSelf )->goTo( hb_parnl( 1 ) );

	hb_itemReturn( pSelf );
}

static void THBARRAY_GOTOP( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();

	_GETOBJC1( pSelf )->goTo( 1 );

	hb_itemReturn( pSelf );
}

static void THBARRAY_GOBOTTOM( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();
	THbArray *pObjC = _GETOBJC1( pSelf );

	pObjC->goTo( pObjC->getSize() );

	hb_itemReturn( pSelf );
}

static void THBARRAY_NEXT( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();

	_GETOBJC1( pSelf )->skip( 1 );

	hb_itemReturn( pSelf );
}

static void THBARRAY_PRIOR( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();

	_GETOBJC1( pSelf )->skip( -1 );

	hb_itemReturn( pSelf );
}

static void THBARRAY_SKIP( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();

	_GETOBJC1( pSelf )->skip( hb_parnldef( 1, 1 ) );

	hb_itemReturn( pSelf );
}

static void THBARRAY_RECNO( void )
{
	hb_retnint( _GETOBJC0()->getPos() );
}

static void THBARRAY_BOF( void )
{
	hb_retl( _GETOBJC0()->bFirst );
}

static void THBARRAY_EOF( void )
{
	hb_retl( _GETOBJC0()->bLast );
}

static void THBARRAY_LEN( void )
{
	hb_retnint( _GETOBJC0()->getSize() );
}

static void THBARRAY_VALUE( void )
{
	THbArray *pObjC = _GETOBJC0();

	hb_itemReturn( pObjC->value( hb_parnsdef( 1, pObjC->FPos ) ) );
}

static void THBARRAY_CURRENT( void )
{
	hb_itemReturn( _GETOBJC0()->current() );
}

static void THBARRAY_SKIPPER( void )
{
	hb_retns( _GETOBJC0()->skipped( hb_parns( 1 ) ) );
}

static void THBARRAY_FREE( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();
	THbArray *pObjC = _GETOBJC1( pSelf );

	delete pObjC;
	pObjC = nullptr;
	hb_arraySetPtr( pSelf, _OBJC_POS, pObjC );
}

//-----------------------------------------------------------------------------
// Funcion de clase para usar desde Harbour
//-----------------------------------------------------------------------------

HB_FUNC( THBARRAY )
{
	static HB_USHORT usClassH = 0;
	THbArray *pObjC;

	pObjC = new THbArray; // Crea el objeto de C++

	if( usClassH == 0 )
	{
		usClassH = pObjC->createClass( _NUN_VARS, "THBARRAY" );
	}

	// Instancia un objeto de la clase THBARRAY y lo mete en la pila
	hb_clsAssociate( usClassH );
	// Asigna el objeto C++ a la data del objeto de xBase
	hb_arraySetPtr( hb_stackReturnItem(), _OBJC_POS, pObjC );
}

//-----------------------------------------------------------------------------
// Inicializa los simbolos de las clase en la tabla de simbolos de harbour.
//-----------------------------------------------------------------------------

HB_INIT_SYMBOLS_BEGIN( THBARRAY__InitSymbols )
{
	"THBARRAY", {HB_FS_PUBLIC | HB_FS_LOCAL}, {HB_FUNCNAME( THBARRAY )}, nullptr
}
HB_INIT_SYMBOLS_END( THBARRAY__InitSymbols )

#if defined(HB_PRAGMA_STARTUP)
	#pragma startup THBARRAY__InitSymbols
#elif defined(HB_DATASEG_STARTUP)
	#define HB_DATASEG_BODY HB_DATASEG_FUNC(THBARRAY__InitSymbols)
	#include "hbiniseg.h"
#endif

//-----------------------------------------------------------------------------
