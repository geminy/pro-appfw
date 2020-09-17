/**
 * @file FileLoader.h
 * @brief class EFileLoader
 */

#ifndef EVO_FILELOADER_H
#define EVO_FILELOADER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <string>

class EView;

/**
 * @class EFileLoader
 * @brief Qml file loader
 */
// TODO
// format: qrc:///app/file
// example: qrc:///QmlDemo/Home.qml
class EVO_APICALL EFileLoader
{
public:
    ~EFileLoader();

    EView* loadQmlView(const std::string &name);

private:
    friend class EApplication;

    EFileLoader();

    BOOL isValidPath(const std::string &path) const;
    std::string viewName2Path(const std::string &name) const;
};

#endif // EVO_FILELOADER_H
