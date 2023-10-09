-- tiki_core

module:add_include_dir( "include" )

module:add_files( "include/tiki/*.h" )
module:add_files( "src/*.inl" )
module:add_files( "src/*.cpp" )
module:add_files( "src/*.natvis" )
