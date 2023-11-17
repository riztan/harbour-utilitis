//-----------------------------------------------------------------------------
// Clase THbArray
// Autor: Manu Expósito
// include
//-----------------------------------------------------------------------------

#pragma once
#ifndef _THBARRAY_H
#define _THBARRAY_H

//-----------------------------------------------------------------------------

#include "hbobject.h"

//-----------------------------------------------------------------------------

const HB_SIZE _OBJC_POS = 1;
const HB_UINT _NUN_VARS = 1;

//-----------------------------------------------------------------------------

class THbArray : public THbObject
{
	public:
		//---------------------------------------------------------------------
		// Propiedades
		PHB_ITEM FArray;
		HB_SIZE FPos;
		HB_BOOL bFirst;
		HB_BOOL bLast;
		//---------------------------------------------------------------------
		// Constructor y destructor desde C++
		THbArray( void );
		virtual ~THbArray( void );
		//---------------------------------------------------------------------
		void init( void ) override;
		void init( PHB_ITEM ) override;
		void addMethods( HB_USHORT ) const override;
		//---------------------------------------------------------------------
		// Metodos de mantenimiento
		HB_BOOL append( PHB_ITEM );
		HB_BOOL insert( PHB_ITEM );
		HB_BOOL update( PHB_ITEM );
		HB_BOOL erase( void ); // Delete
		//---------------------------------------------------------------------
		// Metodos de movimiento
		void goTo( HB_SIZE );
		void skip( HB_ISIZ );
		HB_SIZE getPos( void ) const;
		HB_SIZE getSize( void ) const;
		HB_ISIZ skipped( HB_ISIZ lSkip );
		//---------------------------------------------------------------------
		PHB_ITEM value( HB_SIZE nPos ) const;
		PHB_ITEM current( void ) const;
};

//-----------------------------------------------------------------------------
// Declaración de funciones públicas.

HB_FUNC( THBARRAY ); // Funcion de clase xBase

//-----------------------------------------------------------------------------

#endif      // Fin de _THBARRAY_H

//-----------------------------------------------------------------------------
