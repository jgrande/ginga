
ADD_BOOST_COMPONENTS( system filesystem thread)

ADD_INTERNAL_COMPONENTS( ncl30 )

find_package( XercesC REQUIRED )
ADD_DEPENDENTS( XERCESC )