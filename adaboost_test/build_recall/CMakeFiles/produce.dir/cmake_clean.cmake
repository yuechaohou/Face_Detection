file(REMOVE_RECURSE
  "produce.pdb"
  "produce"
)

# Per-language clean rules from dependency scanning.
foreach(lang)
  include(CMakeFiles/produce.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
