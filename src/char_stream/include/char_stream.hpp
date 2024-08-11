class char_stream {
public:
	virtual wchar_t peek() = 0;
	virtual wchar_t get() = 0;
	virtual bool is_end() = 0;
};