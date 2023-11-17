//-----------------------------------------------------------------------------
// Archivo: HbObject.h
// Autor: Manu Exposito 2023
//-----------------------------------------------------------------------------

#pragma once

#include <hbapi.h>
#include <hbapiitm.h>
#include <hbapicls.h>
#include <hbstack.h>
#include <hbapigt.h>

class THbObject 
{
	public:
		// Operador de reserva de memoria ( se se usa hay que liberar delete )
		void *operator new( size_t size )
		{
			return hb_xgrab( size );
		}

		// Operador de reserva de memoria ( libera memoria se se ha usado new )
		void operator delete( void *pVoid )
		{
			hb_xfree( pVoid );
		}

		// Constructor y destructor por defecto
		THbObject() = default;
		virtual ~THbObject() = default;

		// Crear la clase Hb
		HB_USHORT createClass( HB_USHORT usSize, const char *szClassName ) const 
		{
			HB_USHORT usClassH = hb_clsCreate( usSize, szClassName );
			addMethods( usClassH );
			return usClassH;
		}

		// Obtener el objeto C++ desde la pila
		static void *getObjC() 
		{
			return hb_arrayGetPtr( hb_stackSelfItem(), 1 );
		}

		// Obtener el objeto C++ del objeto xBase pasado como parametro
		static void *getObjC( PHB_ITEM pSelf ) 
		{
			return hb_arrayGetPtr( pSelf, 1 );
		}

		//---------------------------------------------------------------------
		// Metodos de depuracion desde Lenguaje C

		// Para cadenas
		static void OutDbg( const char *szTxt ) 
		{
			PHB_ITEM cTxt = hb_itemNew( nullptr );
			PHB_ITEM aOpt = hb_itemArrayNew( 1 );

			hb_itemPutC( cTxt, szTxt );
			hb_arraySetC( aOpt, 1, "OK" );

			hb_gtAlert( cTxt, aOpt, 0, 0, 0 );
			hb_itemRelease( cTxt );
			hb_itemRelease( aOpt );
		}

		// Para numeros
		static void OutDbg( double dNum ) 
		{
			char szTxt[ 32 ];

			hb_dblToStr( szTxt, sizeof( szTxt ), dNum, 6 );
			OutDbg( szTxt );
		}

		//---------------------------------------------------------------------
		// Metodos virtuales puros que se desarrollan en las clases hijas.
		//---------------------------------------------------------------------
		// El metodo init es llamado desde el metodo new de la clase harbour
		virtual void init( void ) = 0; // Sin parametros
		virtual void init( void * ) = 0; // Puede ser PHB_ITEM 
		// virtual void destroy( void * ) = 0; // Destructor 
		// El metodo addMethods es llamado desde la funcion de la clase harbour  
		// y para la herencia desde harbour desde C++
		virtual void addMethods( HB_USHORT ) const = 0;		
};
