require 'testSystem.testSystem'

-- get
assertNoThrow( function () var = settings.system.ncl.version end )
-- set
assertThrow( function () settings.system.ncl.version = "string" end )
-- default values
assertTrue( settings.system.ncl.version == "3.0", "NCL version expected 3.0")
