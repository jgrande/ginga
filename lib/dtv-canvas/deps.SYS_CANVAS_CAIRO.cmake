Find_Package( GDK-PixBuf REQUIRED )
Find_Package( Glib REQUIRED )
Find_Package( Pango REQUIRED )
Find_Package( Cairo REQUIRED )

ADD_DEPENDENTS( GDK-PIXBUF GLIB PANGO CAIRO )
