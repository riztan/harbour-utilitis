//-----------------------------------------------------------------------------
// Ejemplo 3
// Autor: Manu Expósito
//-----------------------------------------------------------------------------

#define __ROWS__  MaxRow()-2
#define __COLS__  MaxCol()-2

procedure main()

   local oBrws := TBrowse():new( 5, 5, __ROWS__-1, __COLS__-1 )
   local aTest := { "Fila 01", "Fila 02", "Fila 03", "Fila 04", "Fila 05", ;
                    "Fila 06", "Fila 07", "Fila 08", "Fila 09", "Fila 10", ;
                    "Fila 11", "Fila 12", "Fila 13", "Fila 14", "Fila 15", ;
                    "Fila 16", "Fila 17", "Fila 18", "Fila 19", "Fila 20"  }
   local a := THbArray():new( aTest )
   local nCursor
   local cColor
   local nRow, nCol 

   CLS

   with object oBrws
      :colorSpec     := "W+/B, N/BG"
      :ColSep        := hb_UTF8ToStrBox( "│" )
      :HeadSep       := hb_UTF8ToStrBox( "╤═" )
      :FootSep       := hb_UTF8ToStrBox( "╧═" )
      :GoTopBlock    := { || a:first() }
      :GoBottomBlock := { || a:last() }
      :SkipBlock     := { | nSkip | a:skipper( nSkip ) } 

      :AddColumn( TBColumnNew( "Cabecera",  { || a:current() } ) )
      :GetColumn( 1 ):Footing := "Pie"
      :Configure()

      :Freeze := 1
   end with
   
   nCursor := SetCursor( 0 )
   cColor  := SetColor( "W+/B" )
   nRow    := Row()
   nCol    := Col()
   hb_DispBox( 4, 4, __ROWS__, __COLS__, hb_UTF8ToStrBox( "┌─┐│┘─└│ " ) )

   while .t.
      oBrws:ForceStable()
      if oBrws:applykey( Inkey( 0 ) ) == -1
         exit
      endif
   enddo
   
   SetPos( nRow, nCol )
   SetColor( cColor )
   SetCursor( nCursor )

   a:free()

return

//-----------------------------------------------------------------------------
#include "utiles.prg"
//-----------------------------------------------------------------------------
