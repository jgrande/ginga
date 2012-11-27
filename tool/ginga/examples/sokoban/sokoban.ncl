<?xml version="1.0" encoding="ISO-8859-1"?>
<!--
/*******************************************************************************

  Copyright 2010 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of Ginga implementation.

    This program is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    Ginga is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementación de Ginga.

    Este programa es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los términos de la Licencia Pública General GNU como es publicada por la
  Free Software Foundation, según la versión 2 de la licencia.

    Ginga se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANTÍA; ni siquiera la garantía implícita de COMERCIALIZACIÓN o ADECUACIÓN
  PARA ALGÚN PROPÓSITO PARTICULAR. Para más detalles, revise la Licencia Pública
  General GNU.

    Ud. debería haber recibido una copia de la Licencia Pública General GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/
-->

<ncl id="sokoban" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<regionBase>
			<region id="mainReg" width="100%" height="100%"/>
		</regionBase>
		
		<descriptorBase>
			<descriptor id="descImagen"  region="mainReg" />
			<descriptor id="descLua" focusIndex="appFocus" region="mainReg"/>
		</descriptorBase>
		
		<connectorBase>
			<causalConnector id="onSelectionStopSetStart">
				<connectorParam name="key"/>
					<connectorParam name="var"/>
				<simpleCondition role="onSelection" key="$key"/>
				<compoundAction operator="seq">
					<simpleAction role="stop"/>		
					<simpleAction role="set" value="$var" max="unbounded" qualifier="seq"/>
					<simpleAction role="start" max="unbounded" qualifier="seq"/>
				</compoundAction>				
			</causalConnector>
		</connectorBase>
	</head>

	<body>
		<!-- Lo muestro desde el principio para evitar el retardo de renderizado cunado se pulsaba OK -->
		<port id="pEntry" component="appBackground" />
		<port id="pEntry2" component="splashImage"/>						
		
		<media id="foco" type="application/x-ginga-settings">
			<property name="service.currentKeyMaster" value="1"/>
		</media>
		<media id="splashImage" src="images/inicio.jpg" descriptor="descImagen"/>
		<media id="appBackground" src="images/fondo.jpg" descriptor="descImagen"/>
		<media id="application" src="main.lua" descriptor="descLua"/>

		<!-- Link para PC -->
		<link xconnector="onSelectionStopSetStart">
			<linkParam name="key" value="ENTER"/>
			<bind role="onSelection" component="splashImage" />
			<bind role="stop" component="splashImage" />
			<bind role="set" component="foco" interface="service.currentKeyMaster">
				<bindParam name="var" value="appFocus"/>		
			</bind>
			<!-- <bind role="start" component="appBackground"/> -->
			<bind role="start" component="application" />
		</link>

		<!-- Link para el STB -->
		<link xconnector="onSelectionStopSetStart">
			<linkParam name="key" value="OK"/>
			<bind role="onSelection" component="splashImage" />
			<bind role="stop" component="splashImage" />
			<bind role="set" component="foco" interface="service.currentKeyMaster">
				<bindParam name="var" value="appFocus"/>		
			</bind>
		<!--<bind role="start" component="appBackground"/>-->
			<bind role="start" component="application" />
		</link>
	</body>
</ncl>
