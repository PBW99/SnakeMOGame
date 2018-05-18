#pragma once

class InputState
{
public:
	bool mLeftKey;
	bool mRightKey;
	bool mUpKey;
	bool mDownKey;

	float mDesiredHorizontal = 0.f;
	float mDesiredVertical= 0.f;

	float GetDesiredHorizontalDelta()	const {
		return (float)(mLeftKey- mRightKey);
	}
	float GetDesiredVerticalDelta()		const {
		return (float)(mUpKey- mDownKey);
	}
	bool Write(OutputMemoryBitStream& inOutputStream) const;
	bool Read(InputMemoryBitStream& inInputStream);

};
