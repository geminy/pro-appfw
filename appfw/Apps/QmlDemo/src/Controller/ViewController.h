/**
 * @file ViewController.h
 * @brief class EVO_ViewController
 */

#ifndef EVO_VIEWCONTROLLER_H
#define EVO_VIEWCONTROLLER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "ui/ViewCreator.h"

#include <string>

/**
 * @class EVO_ViewController
 * @brief Native view controller
 */
class EVO_ViewController: public EViewCreator
{
public:
    EVO_ViewController();
    ~EVO_ViewController();

    std::string startView();
};

#endif // EVO_VIEWCONTROLLER_H
