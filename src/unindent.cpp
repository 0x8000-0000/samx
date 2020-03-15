/*
   Copyright 2020 Florin Iucha

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "normalizer.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>


int main(int argc, char* argv[])
{
   if (argc < 2)
   {
      std::cerr << "Error: input / output arguments missing\n";
      return 1;
   }

   std::ifstream input(argv[1]);
   std::ofstream output(argv[2]);

   sam2::Normalizer normalizer{output};

   const auto size = normalizer.normalize(input);
   std::cerr << "Processed " << size << " bytes\n";

   return 0;
}
