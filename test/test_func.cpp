/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  test_func.cpp
 * Description :  Contains the helper functions to use in test code only
 \***************************************************************************/

#include "test_precomp.hpp"

// TODO: make it OS independent
#include <dirent.h> // only works for linux

using namespace FFR;

namespace test_FFR {

std::vector<std::string> getAllFilesFromFolder(const std::string& folder,
                                               bool ignoreHiddenFiles,
                                               const std::string& fileExt) {
  std::vector<std::string> files;

#ifdef WITH_CLASS_NAME
  std::string _className("-");
#endif

  do {  // for common error handling
    struct dirent *dir_entry;
    DIR *dp;
    dp = opendir(folder.c_str());
    if (dp == NULL) {
      DEBUGLE("opendir: Path does not exist or could not be read.");
      break;
    }
    while ((dir_entry = readdir(dp))) {
      if (ignoreHiddenFiles && (dir_entry->d_name[0] == '.'))
        continue;
      if (strstr(dir_entry->d_name, fileExt.c_str())) {
        std::string fileName = /*folder +*/std::string(dir_entry->d_name);
        files.push_back(fileName);
        DEBUGLD("found file: %s\n", fileName.c_str());
      }
    }
    closedir(dp);
  } while (0);
  return files;
}

}  // namespace test_FFR
