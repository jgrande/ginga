<?xml version="1.0" encoding="ISO-8859-1"?>
<ncl id="test_media_fontColor_9" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<regionBase>
			<region id="reg1"/>
		</regionBase>
		<descriptorBase>
			<descriptor id="desc1" region="reg1" >
			</descriptor>
		</descriptorBase>
	</head>

	<body>
		<port id="port1" component="image1" />
		<port id="port2" component="image2" />
		<media id="image1" src="../../../../text/sample_chars_ISO-8859-1.txt" descriptor="desc1">
				<property name="fontColor" value="red" />
				<property name="fontSize" value="10" />
				<property name="fontFamily" value="Tiresias" />
		</media>
		<media id="image2" src="../../../../text/sample_chars_UTF-8.txt" descriptor="desc1">
				<property name="fontColor" value="red" />
				<property name="fontSize" value="10" />
				<property name="fontFamily" value="Tiresias" />
				<property name="left" value="50%" />
		</media>
	</body>
</ncl>
