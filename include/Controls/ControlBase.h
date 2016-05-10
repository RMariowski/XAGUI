#ifndef XAGUI_CONTROL_BASE_H
#define XAGUI_CONTROL_BASE_H

XAGUI_EXPORT class ControlBase
{
	public:

		ControlBase();

		virtual inline cchar* GetID() const { return _id.c_str(); }

		virtual inline void SetID(cchar* id) { _id = id; }

	protected:

		std::string _id;
};

#endif