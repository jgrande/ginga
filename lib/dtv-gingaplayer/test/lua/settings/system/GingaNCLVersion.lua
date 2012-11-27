require 'testSystem.testSystem'

-- get
assertNoThrow( function () var = settings.system.GingaNCL.version end )
-- set
assertThrow( function () settings.system.GingaNCL.version = "string" end )
-- default values
assertTrue( settings.system.GingaNCL.version == "Ginga.ar 2.0", "GingaNCL version expected: Ginga.ar 2.0")


