<?xml version="1.0" encoding="ISO-8859-1"?>
<!-- Generated by NCL Eclipse -->
<ncl id="mainMenu" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<ruleBase>
			<rule id="rInteractivity" var="menuOption" comparator="eq" value="INFO"/>
			<rule id="rRed" var="menuOption" comparator="eq" value="RED"/>
			<rule id="rGreen" var="menuOption" comparator="eq" value="GREEN"/>
			<rule id="rYellow" var="menuOption" comparator="eq" value="YELLOW"/>
			<rule id="rBlue" var="menuOption" comparator="eq" value="BLUE"/>
			<rule id="rInitial" var="menuOption" comparator="eq" value="INITIAL"/>
			<rule id="r640x480" var="system.screenGraphicSize" comparator="eq" value="640,480"/>
		
		</ruleBase>
		<regionBase>
				
			
			<region id="bgReg">
				<region id="infoReg" height="8%" width="7%" left="9%" bottom="5%"/>
				<region id="menuReg" height="90%" width="28%" left="64%"  bottom="4%" zIndex="2">
					<region id="tituloTextoReg" height="25%" width="90%" left="13.5%" bottom="78%"/>	
					<region id="textoReg" height="75%" width="90%" left="13.5%"  />
				</region>
			</region>

		</regionBase>
		<descriptorBase>

			<descriptor id="bgDesc" region="bgReg" focusIndex="appFocus" />
			<descriptor id="infoDesc" region="infoReg"  focusBorderWidth="0"/>
			<descriptor id="menuDesc" region="menuReg" focusBorderWidth="0"/>
		
	<!--descriptor RED-->		
			<descriptorSwitch id="textoDescRED">
				<bindRule constituent="seiscientosDescRED" rule="r640x480"/>
				<defaultDescriptor descriptor="defaultDescRED"/>
							
				<descriptor id="seiscientosDescRED" region="textoReg">
					<descriptorParam name="fontSize" value="11"/>					
				</descriptor>
				<descriptor id="defaultDescRED" region="textoReg">
					<descriptorParam name="fontSize" value="13"/>					
				</descriptor>
			
			</descriptorSwitch>
			
			
			<descriptorSwitch id="tituloTextoDescRED">
				<bindRule constituent="seiscientosTitDescRED" rule="r640x480"/>
							
				<defaultDescriptor descriptor="defaultTitDescRED"/>
				
				<descriptor id="seiscientosTitDescRED" region="tituloTextoReg">
					<descriptorParam name="fontSize" value="13"/>					
				</descriptor>
				<descriptor id="defaultTitDescRED" region="tituloTextoReg">
					<descriptorParam name="fontSize" value="14"/>					
				</descriptor>
			</descriptorSwitch>
	<!--descriptor GREEN-->			
			<descriptorSwitch id="textoDescGREEN">
				<bindRule constituent="seiscientosDescGREEN" rule="r640x480"/>
				
				
				
				<defaultDescriptor descriptor="defaultDescGREEN"/>
							
				<descriptor id="seiscientosDescGREEN" region="textoReg">
					<descriptorParam name="fontSize" value="11"/>					
				</descriptor>
				<descriptor id="defaultDescGREEN" region="textoReg">
					<descriptorParam name="fontSize" value="13"/>					
				</descriptor>
			
			</descriptorSwitch>
			
			
			<descriptorSwitch id="tituloTextoDescGREEN">
				<bindRule constituent="seiscientosTitDescGREEN" rule="r640x480"/>
			
				
				<defaultDescriptor descriptor="defaultTitDescGREEN"/>
				
				<descriptor id="seiscientosTitDescGREEN" region="tituloTextoReg">
					<descriptorParam name="fontSize" value="13"/>					
				</descriptor>
				<descriptor id="defaultTitDescGREEN" region="tituloTextoReg">
					<descriptorParam name="fontSize" value="15"/>					
				</descriptor>
			</descriptorSwitch>
			
	<!--descriptor YELLOW-->		
	
			<descriptorSwitch id="textoDescYELLOW">
				<bindRule constituent="seiscientosDescYELLOW" rule="r640x480"/>
				
				
				
				<defaultDescriptor descriptor="defaultDescYELLOW"/>
							
				<descriptor id="seiscientosDescYELLOW" region="textoReg">
					<descriptorParam name="fontSize" value="11"/>					
				</descriptor>
				<descriptor id="defaultDescYELLOW" region="textoReg">
					<descriptorParam name="fontSize" value="14"/>					
				</descriptor>
			
			</descriptorSwitch>
			
			<descriptorSwitch id="tituloTextoDescYELLOW">
				<bindRule constituent="seiscientosTitDescYELLOW" rule="r640x480"/>
			
				
				<defaultDescriptor descriptor="defaultTitDescYELLOW"/>
				
				<descriptor id="seiscientosTitDescYELLOW" region="tituloTextoReg">
					<descriptorParam name="fontSize" value="11"/>					
				</descriptor>
				<descriptor id="defaultTitDescYELLOW" region="tituloTextoReg">
					<descriptorParam name="fontSize" value="14"/>					
				</descriptor>
			</descriptorSwitch>
	<!--descriptor BLUE-->
			<descriptorSwitch id="textoDescBLUE">
				<bindRule constituent="seiscientosDescBLUE" rule="r640x480"/>
				
				
				
				<defaultDescriptor descriptor="defaultDescBLUE"/>
							
				<descriptor id="seiscientosDescBLUE" region="textoReg">
					<descriptorParam name="fontSize" value="11"/>					
				</descriptor>
				<descriptor id="defaultDescBLUE" region="textoReg">
					<descriptorParam name="fontSize" value="13"/>					
				</descriptor>
			
			</descriptorSwitch>

			<descriptorSwitch id="tituloTextoDescBLUE">
				<bindRule constituent="seiscientosTitDescBLUE" rule="r640x480"/>
			
				
				<defaultDescriptor descriptor="defaultTitDescBLUE"/>
				
				<descriptor id="seiscientosTitDescBLUE" region="tituloTextoReg">
					<descriptorParam name="fontSize" value="11"/>					
				</descriptor>
				<descriptor id="defaultTitDescBLUE" region="tituloTextoReg">
					<descriptorParam name="fontSize" value="13"/>					
				</descriptor>
			</descriptorSwitch>
			
		</descriptorBase>
		<connectorBase>

			
			<causalConnector id="onEndAttributionStopSetStart">
				<connectorParam name="var"/>				
				
				<simpleCondition role="onEndAttribution"  max="unbounded"  qualifier="or"/>			
				<compoundAction operator="seq">
					<simpleAction role="stop" max="unbounded" qualifier="seq"/>
					<simpleAction role="set" value="$var"  max="unbounded" qualifier="seq"/>
					<simpleAction role="start"  max="unbounded" qualifier="seq"/>					
				</compoundAction>	
				
			</causalConnector>
			<causalConnector id="onEndAttributionTestSetStart">
				<connectorParam name="var"/>	
				<connectorParam name="value"/>

							
				<compoundCondition operator="and">

					<simpleCondition role="onEndAttribution"  max="unbounded"  qualifier="or"/>
					<assessmentStatement comparator="eq">

						<attributeAssessment role="test" eventType="attribution" />

						<valueAssessment value="$value"/>

						

					</assessmentStatement>	

				</compoundCondition>
							
				<compoundAction operator="seq">
			
					<simpleAction role="set" value="$var"  max="unbounded" qualifier="seq"/>
					<simpleAction role="start"  max="unbounded" qualifier="seq"/>					
				</compoundAction>	
				
			</causalConnector>
			<causalConnector id="onEndAttributionTestSetStop">
				<connectorParam name="var"/>	
				<connectorParam name="value"/>
							
				<compoundCondition operator="and">
					<simpleCondition role="onEndAttribution"  max="unbounded"  qualifier="or"/>
					<assessmentStatement comparator="eq">
						<attributeAssessment role="test" eventType="attribution" />
						<valueAssessment value="$value"/>
						
					</assessmentStatement>	
				</compoundCondition>
							
				<compoundAction operator="seq">
			
					<simpleAction role="set" value="$var"  max="unbounded" qualifier="seq"/>
					<simpleAction role="stop"  max="unbounded" qualifier="seq"/>					
				</compoundAction>	
				
			</causalConnector>

		</connectorBase>
	</head>

	<body id="body">
		<port id="p0" component="application"/>
		<port id="p1" component="bg"/>
		
		
		
		
		
		

		<!--MEDIAS-->
			
		
			
			
			
				<!--SWITCH de opciones de menu-->
		
					<switch id="sOptions">
						<bindRule constituent="cInitial" rule="rInitial"/>
						<bindRule constituent="cRedMenu" rule="rRed"/>			
						<bindRule constituent="cGreenMenu" rule="rGreen"/>
						<bindRule constituent="cYellowMenu" rule="rYellow"/>
						<bindRule constituent="cBlueMenu" rule="rBlue"/>
						<bindRule constituent="cInfo" rule="rInteractivity"/>
								
						<context id="cInfo">
							<port id="cI0" component="info"/>
							
							<media id="info" descriptor="infoDesc" src="./resources/images/FutbolUltimo/INFO_Gris.jpg">
								
							</media>
						</context>
						
	
						<context id="cInitial">
							<port id="pInitial" component="menu"/>
							<media id="menu" src="./resources/images/FutbolUltimo/Menu0.jpg" descriptor="menuDesc">
								<property name="height" value="18%"/>							
							</media>
						</context>
	
						<context id="cRedMenu">
							<port id="pRedMenu0" component="menuRED"/>
							<port id="pRedMenu1" component="tituloTextoRED"/>
							<port id="pRedMenu2" component="textoRED"/>
							
							<media id="tituloTextoRED" src="./resources/images/FutbolUltimo/ttextoRED.txt" descriptor="tituloTextoDescRED" >
									<property name="visible"/>
									<property name="fontVariant" value="small-caps"/>
									<property name="fontFamily" value="Tiresias"/>					
									<property name="fontWeight" value="bold"/>														
									<property name="fontColor" value="black"/>
									<property name="bottom" value="68%"/>										
						
							</media>
							<media id="textoRED" src="./resources/images/FutbolUltimo/textoRED.txt" descriptor="textoDescRED" >
				
									<property name="visible"/>		
									<property name="fontFamily" value="Tiresias"/>	
									<property name="fontWeight" value="bold"/>				
									
									<property name="fontColor" value="black"/>
									<property name="bottom" value="11%"/>
														
					
							</media>
							<media id="menuRED" src="./resources/images/FutbolUltimo/Menu1-ROJO.jpg" descriptor="menuDesc" />
						
						</context>
						<context id="cGreenMenu">
							<port id="pGreenMenu0" component="menuGREEN"/>
							<port id="pGreenMenu1" component="tituloTextoGREEN"/>
							<port id="pGreenMenu2" component="textoGREEN"/>
							
							<media id="tituloTextoGREEN" src="./resources/images/FutbolUltimo/ttextoGREEN.txt" descriptor="tituloTextoDescGREEN" >
									<property name="visible"/>
									<property name="fontVariant" value="small-caps"/>				
									<property name="fontFamily" value="Tiresias"/>								
									<property name="fontWeight" value="bold"/>				
									<property name="bottom" value="62%"/>
									<property name="fontColor" value="black"/>
												
							</media>
							<media id="textoGREEN" src="./resources/images/FutbolUltimo/textoGREEN.txt" descriptor="textoDescGREEN" >
				
									<property name="visible"/>			
									<property name="fontFamily" value="Tiresias"/>				
									<property name="fontWeight" value="bold"/>				
									<property name="bottom" value="6%"/>
									<property name="fontColor" value="black"/>
															
					
							</media>
							<media id="menuGREEN" src="./resources/images/FutbolUltimo/Menu2-VERDE.jpg" descriptor="menuDesc" />
							
						</context>
						<context id="cYellowMenu">
							<port id="pYellowMenu0" component="menuYELLOW"/>
							<port id="pYellowMenu1" component="tituloTextoYELLOW"/>
							<port id="pYellowMenu2" component="textoYELLOW"/>
							
							<media id="tituloTextoYELLOW" src="./resources/images/FutbolUltimo/ttextoYELLOW.txt" descriptor="tituloTextoDescYELLOW" >
									<property name="visible"/>
									<property name="fontFamily" value="Tiresias"/>		
									<property name="fontVariant" value="small-caps"/>					
									<property name="fontWeight" value="bold"/>				
									<property name="bottom" value="57%"/>
									<property name="fontColor" value="black"/>
																	
							</media>
							<media id="textoYELLOW" src="./resources/images/FutbolUltimo/textoYELLOW.txt" descriptor="textoDescYELLOW" >
				
									<property name="visible"/>			
									<property name="fontFamily" value="Tiresias"/>
									<property name="fontWeight" value="bold"/>				
									<property name="top" value="23%"/>
									<property name="fontColor" value="black"/>																		
					
							</media>
							<media id="menuYELLOW" src="./resources/images/FutbolUltimo/Menu3-AMARILLO.jpg" descriptor="menuDesc" />
						</context>
	
						<context id="cBlueMenu">
							<port id="pBlueMenu0" component="menuBLUE"/>
							<port id="pBlueMenu1" component="tituloTextoBLUE"/>
							<port id="pBlueMenu2" component="textoBLUE"/>
							
							<media id="tituloTextoBLUE" src="./resources/images/FutbolUltimo/ttextoBLUE.txt" descriptor="tituloTextoDescBLUE" >
									<property name="visible"/>
									<property name="fontVariant" value="small-caps"/>					
									<property name="fontFamily" value="Tiresias"/>	
									<property name="fontWeight" value="bold"/>				
									<property name="bottom" value="53%"/>
									<property name="fontColor" value="black"/>
																		
							</media>
							<media id="textoBLUE" src="./resources/images/FutbolUltimo/textoBLUE.txt" descriptor="textoDescBLUE" >
									<property name="visible"/>			
									<property name="fontFamily" value="Tiresias"/>	
									<property name="fontWeight" value="bold"/>				
									<property name="top" value="28%"/>
									<property name="fontColor" value="black"/>														
					
							</media>
	
							<media id="menuBLUE" src="./resources/images/FutbolUltimo/Menu4-AZUL.jpg" descriptor="menuDesc" />
						</context>
					</switch>
	
	<!--SCRIPT-->
		<media id="application" src="main.lua" descriptor="bgDesc">
			<property name="itemChange"/>	
			
			
		</media>

	<!--SETTINGS-->
		<media id="settings" type="application/x-ginga-settings" >

			<property name="service.currentKeyMaster" value="appFocus"/>			
			<property name="menuOption"  />	
			<property name="system.screenGraphicSize"/>
			
			

		</media>
<!--Desde lua se actualizan las reglas en ncl para que las lea el switch de opciones del menu-->
		<link xconnector="onEndAttributionStopSetStart">
			
			<linkParam name="var" value="$getValue"/>
			<bind role="onEndAttribution" component="application" interface="itemChange" />
			<bind role="getValue" component="application" interface="itemChange"/>			
			<bind role="stop" component="sOptions" />
			<bind role="set" component="settings"  interface="menuOption"/>
			<bind role="start" component="sOptions" />
			
		</link>

	
		
	</body>
</ncl>

	