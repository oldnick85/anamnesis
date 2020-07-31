#include "ctrmmain.h"

using namespace TRM_TXT_RES;

void CTrmMain::Begin()
{
    printf("%s\n", text(siMainDescription).c_str());
    bool exit = false;
    while (not exit)
    {
        printf("\n%s\n", text(siHorisontalSeparator).c_str());
        printf("%s:\n 1 - %s\n 2 - %s\n %s - %s\n",
               text(siMainQuestion).c_str(), text(siMainEncodePass).c_str(),
               text(siMainRestorePass).c_str(), text(siOtherVariant).c_str(), text(siExit).c_str());
        int opt;
        InputInt(opt);
        switch (opt)
        {
        case 1:
		{
            ClearScreen();
			CGuiEncode pass_encode;
			pass_encode.Begin();
            break;
		}
        case 2:
		{
            ClearScreen();
			CTrmDecode pass_restore;
			pass_restore.Begin();
            break;
		}
        default:
            exit = true;
            break;
        }
    }
}
