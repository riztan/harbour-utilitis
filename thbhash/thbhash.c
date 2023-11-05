//-----------------------------------------------------------------------------
// Gestion de hash como objetos
//
// Author: Manuel Expósito
//
//-----------------------------------------------------------------------------

#include "hbapiitm.h"
#include "hbvm.h"
#include "hbstack.h"
#include "hbapicls.h"
#include "hboo.ch"
#include "hbinit.h"

HB_FUNC( __GETMESSAGE );
HB_FUNC( __CLSADDMSG );

#define _GETHASH0() hb_arrayGetPtr( hb_stackSelfItem(), 1 )
#define _GETHASH1( pSelf ) hb_arrayGetPtr( (pSelf), 1 )

//-----------------------------------------------------------------------------
// Constructor

static void THBHASH_NEW( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();
	PHB_ITEM hTable;
	PHB_ITEM hTablePar = hb_param( 1, HB_IT_HASH );

	if( hTablePar )
	{
		hTable = hb_itemNew( NULL );
		hb_itemMove( hTable, hTablePar );
	}
	else
	{
		hTable = hb_hashNew( NULL );
	}

	hb_hashClearFlags( hTable, HB_HASH_BINARY );
	hb_hashSetFlags( hTable, HB_HASH_IGNORECASE | HB_HASH_RESORT );
	hb_arraySetPtr( pSelf, 1, hTable );

	hb_itemReturn( pSelf );
}

//-----------------------------------------------------------------------------
// Asigna un nuevo hash para gestionarlo desde el objeto

static void THBHASH_SETHASH( void )
{
	PHB_ITEM pSelf = hb_stackSelfItem();
	PHB_ITEM hTablePar = hb_param( 1, HB_IT_HASH );
	PHB_ITEM hTableOld = _GETHASH1( pSelf );

	if( hTableOld )
	{
		hTableOld = hb_hashNew( hTableOld );
	}

	if( hTablePar )
	{
		PHB_ITEM hTable = hb_itemNew( NULL );

		hb_itemMove( hTable, hTablePar );

		hb_hashClearFlags( hTable, HB_HASH_BINARY );
		hb_hashSetFlags( hTable, HB_HASH_IGNORECASE | HB_HASH_RESORT );
		hb_arraySetPtr( pSelf, 1, hTable );
	}

	hb_itemReturnRelease( hTableOld );
}

//-----------------------------------------------------------------------------
// Obtiene el hash gestionado desde el objeto

static void THBHASH_GETHASH( void )
{
	hb_itemReturn( _GETHASH0() );
}

//-----------------------------------------------------------------------------
// Tamaño

static void THBHASH_LEN( void )
{
	hb_retnint( hb_hashLen( _GETHASH0() ) );
}

//-----------------------------------------------------------------------------
// Elimina

static void THBHASH_DEL( void )
{
	PHB_ITEM pKey = hb_param( 1, HB_IT_HASHKEY );

	hb_retl( pKey ? hb_hashDel( _GETHASH0(), pKey ) : HB_FALSE );
}

//-----------------------------------------------------------------------------
// Añade o modifica

static void THBHASH_SET( void )
{
	PHB_ITEM pKey = hb_param( 1, HB_IT_HASHKEY );

	hb_retl( pKey ? hb_hashAdd( _GETHASH0(), pKey, hb_param( 2, HB_IT_ANY ) ) : HB_FALSE );
}

//-----------------------------------------------------------------------------

static void THBHASH_CLEAR( void )
{
	hb_retl( hb_hashClear( _GETHASH0() ) );
}

//-----------------------------------------------------------------------------

static void THBHASH_SORT( void )
{
	hb_hashSort( _GETHASH0() );

}

//-----------------------------------------------------------------------------
// Busca

static void THBHASH_SCAN( void )
{
	HB_SIZE nPos = 0;
	PHB_ITEM pKey = hb_param( 1, HB_IT_HASHKEY );

	if( pKey )
	{
		hb_hashScan( _GETHASH0(), pKey, &nPos );
	}

	hb_retnint( nPos );
}

//-----------------------------------------------------------------------------
// Array con las claves

static void THBHASH_KEYS( void )
{
	hb_itemReturnRelease( hb_hashGetKeys( _GETHASH0() ) );
}

//-----------------------------------------------------------------------------
// Array con los valores

static void THBHASH_VALUES( void )
{
	hb_itemReturnRelease( hb_hashGetValues( _GETHASH0() ) );
}

//-----------------------------------------------------------------------------
// Valor de la clave

static void THBHASH_GET( void )
{
	PHB_ITEM pKey = hb_param( 1, HB_IT_HASHKEY );

	if( pKey )
	{
		PHB_ITEM pValue = hb_hashGetItemPtr( _GETHASH0(), pKey, HB_HASH_AUTOADD_ACCESS );

		if( pValue )
		{
			hb_itemReturn( pValue );
			return;
		}
	}

	hb_ret();
}

//-----------------------------------------------------------------------------

static void THBHASH_VALUEAT( void )
{
	PHB_ITEM pPos = hb_param( 1, HB_IT_NUMERIC );

	if( pPos )
	{
		PHB_ITEM pValue = hb_hashGetValueAt( _GETHASH0(), hb_itemGetNS( pPos ) );

		if( pValue )
		{
			hb_itemReturn( pValue );
			return;
		}
	}

	hb_ret();
}

//-----------------------------------------------------------------------------

static void THBHASH_KEYAT( void )
{
	PHB_ITEM pPos = hb_param( 1, HB_IT_NUMERIC );

	if( pPos )
	{
		PHB_ITEM pKey = hb_hashGetKeyAt( _GETHASH0(), hb_itemGetNS( pPos ) );

		if( pKey )
		{
			hb_itemReturn( pKey );
			return;
		}
	}

	hb_ret();
}

//-----------------------------------------------------------------------------

static void THBHASH_DELAT( void )
{
	PHB_ITEM pPos = hb_param( 1, HB_IT_NUMERIC );

	if( pPos )
	{
		if( hb_hashDelAt( _GETHASH0(), hb_itemGetNS( pPos ) ) )
		{
			hb_retl( HB_TRUE );
			return;
		}
	}

	hb_retl( HB_FALSE );
}

//-----------------------------------------------------------------------------

static void THBHASH_HASKEY( void )
{
	PHB_ITEM pKey = hb_param( 1, HB_IT_HASHKEY );
	HB_SIZE nPos;

	hb_retl( hb_hashScanSoft( _GETHASH0(), pKey, &nPos ) );
	hb_storns( nPos, 2 );
}

//-----------------------------------------------------------------------------

static void THBHASH_SETFLAGS( void )
{
	PHB_ITEM nFlags = hb_param( 1, HB_IT_INTEGER );

	if( nFlags )
	{
		hb_hashSetFlags( _GETHASH0(), hb_itemGetNI( nFlags ) );
	}
}

//-----------------------------------------------------------------------------

static void THBHASH_GETFLAGS( void )
{
	hb_retni( hb_hashGetFlags( _GETHASH0() ) );
}

//-----------------------------------------------------------------------------

static void THBHASH_CLEARFLAGS( void )
{
	PHB_ITEM nFlags = hb_param( 1, HB_IT_INTEGER );

	if( nFlags )
	{
		hb_hashClearFlags( _GETHASH0(), hb_itemGetNI( nFlags ) );
	}
}

//-----------------------------------------------------------------------------

static void THBHASH_END( void )
{
	hb_itemRelease( _GETHASH0() );
}

//-----------------------------------------------------------------------------

HB_FUNC_STATIC( __THBHASH_ONERROR )
{
	PHB_ITEM pKey;
	char *szKey;

	hb_vmPushDynSym( hb_dynsymGet( "__GETMESSAGE" ) );
	hb_vmPushNil();
	hb_vmProc( 0 );

	pKey = hb_stackReturnItem();
	szKey = hb_itemGetC( pKey );

	if( szKey[ 0 ] == '_' )	// SET
	{
		hb_itemPutC( pKey, szKey + 1 );
		hb_hashAdd( _GETHASH0(), pKey, hb_param( 1, HB_IT_ANY ) );
	}
	else	// GET
	{
		PHB_ITEM pVal = hb_hashGetItemPtr( _GETHASH0(), pKey, 0 );

		pVal ? ( void ) hb_itemReturn( pVal ) : hb_ret();
	}

	hb_xfree( szKey );
}

//-----------------------------------------------------------------------------
// Añade los metodos de la clase

static void addMethods( HB_USHORT usClassH )
{
	// Data hash
	hb_clsAdd( usClassH, "_HASH", THBHASH_SETHASH );
	hb_clsAdd( usClassH, "HASH", THBHASH_GETHASH );
	// Data flags
	hb_clsAdd( usClassH, "_FLAGS", THBHASH_SETFLAGS );
	hb_clsAdd( usClassH, "FLAGS", THBHASH_GETFLAGS );
	// Metodos
	hb_clsAdd( usClassH, "NEW", THBHASH_NEW );
	hb_clsAdd( usClassH, "SETHASH", THBHASH_SETHASH );
	hb_clsAdd( usClassH, "GETHASH", THBHASH_GETHASH );
	hb_clsAdd( usClassH, "LEN", THBHASH_LEN );
	hb_clsAdd( usClassH, "DEL", THBHASH_DEL );
	hb_clsAdd( usClassH, "ADD", THBHASH_SET );
	hb_clsAdd( usClassH, "SET", THBHASH_SET );
	hb_clsAdd( usClassH, "GET", THBHASH_GET );
	hb_clsAdd( usClassH, "CLEAR", THBHASH_CLEAR );
	hb_clsAdd( usClassH, "SORT", THBHASH_SORT );
	hb_clsAdd( usClassH, "SCAN", THBHASH_SCAN );
	hb_clsAdd( usClassH, "KEYS", THBHASH_KEYS );
	hb_clsAdd( usClassH, "VALUES", THBHASH_VALUES );
	hb_clsAdd( usClassH, "VALUEAT", THBHASH_VALUEAT );
	hb_clsAdd( usClassH, "KEYAT", THBHASH_KEYAT );
	hb_clsAdd( usClassH, "DELAT", THBHASH_DELAT );
	hb_clsAdd( usClassH, "HASKEY", THBHASH_HASKEY );
	hb_clsAdd( usClassH, "SETFLAGS", THBHASH_SETFLAGS );
	hb_clsAdd( usClassH, "GETFLAGS", THBHASH_GETFLAGS );
	hb_clsAdd( usClassH, "CLEARFLAGS", THBHASH_CLEARFLAGS );
	hb_clsAdd( usClassH, "END", THBHASH_END );

	// Añade el metodo ONERROR como gestor de errores de la clase
	hb_vmPushDynSym( hb_dynsymGet( "__CLSADDMSG" ) );
	hb_vmPushNil();
	hb_vmPushInteger( usClassH );
	hb_vmPushString( "ONERROR", strlen( "ONERROR" ) );
	hb_vmPushDynSym( hb_dynsymGet( "__THBHASH_ONERROR" ) );
	hb_vmPushInteger( HB_OO_MSG_ONERROR );
	hb_vmProc( 4 );
}

//-----------------------------------------------------------------------------
// Funcion de clase para usar desde Harbour
//-----------------------------------------------------------------------------

HB_FUNC( THBHASH )
{
	static HB_USHORT usClassH = 0;

	if( usClassH == 0 )
	{
		usClassH = hb_clsCreate( 1, "THBHASH" );
		addMethods( usClassH );
	}

	// Instancia un objeto de la clase THBARRAY y lo mete en la pila
	hb_clsAssociate( usClassH );

	// Asigna el objeto C++ a la data del objeto de xBase
	hb_arraySetPtr( hb_stackReturnItem(), 1, NULL );
}

//=============================================================================
// Inicializa los simbolos de las clase en la tabla de simbolos de harbour.
//=============================================================================

HB_INIT_SYMBOLS_BEGIN( THBHASH__InitSymbols )
{ "THBHASH", { HB_FS_PUBLIC | HB_FS_LOCAL }, { HB_FUNCNAME( THBHASH ) }, NULL },
{ "__GETMESSAGE", { HB_FS_PUBLIC | HB_FS_LOCAL }, { HB_FUNCNAME( __GETMESSAGE ) }, NULL },
{ "__CLSADDMSG", { HB_FS_PUBLIC | HB_FS_LOCAL }, { HB_FUNCNAME( __CLSADDMSG ) }, NULL },
{ "__THBHASH_ONERROR", { HB_FS_PUBLIC | HB_FS_LOCAL }, { HB_FUNCNAME( __THBHASH_ONERROR ) }, NULL }
HB_INIT_SYMBOLS_END( THBPGPP__InitSymbols )

#if defined( HB_PRAGMA_STARTUP )
	#pragma startup THBHASH__InitSymbols
#elif defined( HB_DATASEG_STARTUP )
	#define HB_DATASEG_BODY HB_DATASEG_FUNC( THBHASH__InitSymbols )
	#include "hbiniseg.h"
#endif

//-----------------------------------------------------------------------------

