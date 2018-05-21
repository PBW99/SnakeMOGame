#include "SnakeClientPCH.h"


namespace {
    float kTimeBetweenInputSamples = 0.01f;
}
#if !_WIN32
#include <curses.h>
#endif

InputManager::InputManager() {
#if !_WIN32
    initscr();
    nodelay(stdscr, TRUE);
#endif
}

InputManager::~InputManager() {
#if !_WIN32
    endwin();
#endif
}


void InputManager::HandleInput() {
    mCurState.mLeftKey = false;
    mCurState.mRightKey = false;
    mCurState.mUpKey = false;
    mCurState.mDownKey = false;


#if _WIN32
    if (kbhit(VK_LEFT) & 0x8001)
    {
        mCurState.mLeftKey = true;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
    {
        mCurState.mRightKey = true;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8001)
    {
        mCurState.mUpKey = true;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8001)
    {
        mCurState.mDownKey = true;
    }
#else

//http://blog.naver.com/PostView.nhn?blogId=sharonichoya&logNo=220875372940&parentCategoryNo=&categoryNo=18&viewDate=&isShowPopularPosts=true&from=search
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            mCurState.mLeftKey = true;
            break;
        case KEY_RIGHT:
            mCurState.mRightKey= true;
            break;
        case KEY_UP:
            mCurState.mUpKey= true;
            break;
        case KEY_DOWN:
            mCurState.mDownKey= true;
            break;
    }
#endif


}


const Move &InputManager::SampleInputAsMove() {
    return mMoveList.AddMove(mCurState, Timing::sInstance.GetFrameStartTime());
}

bool InputManager::IsTimeToSampleInput() {
    float time = Timing::sInstance.GetFrameStartTime();
    if (time > mNextTimeToSampleInput) {
        mNextTimeToSampleInput = mNextTimeToSampleInput + kTimeBetweenInputSamples;
        return true;
    }

    return false;
}

bool InputManager::IsSomethingInputed() {
    if (mCurState.mLeftKey == false && mCurState.mRightKey == false && mCurState.
            mUpKey == false && mCurState.mDownKey == false) {
        return false;
    }
    return true;
}

void InputManager::Update() {
    HandleInput();
//	if (IsTimeToSampleInput() &&  IsSomethingInputed())
    if (IsTimeToSampleInput()) {
        mPendingMove = &SampleInputAsMove();
    }
}


