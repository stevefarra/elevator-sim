/* Allows incoming commands that have been validated by the IO process
 * to be given to the Dispatcher, where upon the Dispatcher decides
 * which elevator to delegate the command to (e.g. floor or up/down request)
 */

#pragma once
#include "rt.h"

CTypedPipe<int> IOAndDispatcherPipeline("IOAndDispatcherPipeline", 100);
