#ifndef XAGUI_PROGRESS_BAR_H
#define XAGUI_PROGRESS_BAR_H

XAGUI_EXPORT class ProgressBar : public Button
{
	public:

		ProgressBar();

		virtual void Render();

		virtual inline uint8_t GetProgress() const { return _progress; }

		virtual void SetProgress(int8_t progress);

	public:

		virtual void OnValueChanged();
	
	public:

		OnValueChangedEvent onValueChanged;

	protected:

		int8_t _progress;
};

#endif