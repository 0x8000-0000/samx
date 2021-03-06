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
#include "samx_parser.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

int main(int argc, char* argv[])
{
   if (argc < 2)
   {
      std::cerr << "Error: input / output arguments missing\n";
      return 1;
   }

   std::ifstream input{argv[1]};
   if (!input)
   {
      std::cerr << "Cannot open input file " << argv[1] << '\n';
      return 2;
   }

   std::ostringstream dedentStream;

   samx::Normalizer normalizer{dedentStream};

   normalizer.normalize(input);

   std::ostream* output = &std::cout;

   std::unique_ptr<std::ofstream> fileOutput;

   if (argc > 2)
   {
      fileOutput = std::make_unique<std::ofstream>(argv[2]);
      output     = fileOutput.get();
   }

   try
   {
      const auto doc = samx::parse(dedentStream.str());

      std::cerr << "Found " << doc.getBlockCount() << " top level blocks\n";

      *output << doc << "\n";
   }
   catch (const std::runtime_error& re)
   {
      std::cerr << "Exception: " << re.what() << std::endl;
   }

   return 0;
}
