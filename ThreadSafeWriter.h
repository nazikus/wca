namespace ua { namespace kiev { namespace ukma { namespace downloader {
	
	/**
	This class will be used to write messages in multi-threaded environment. 
	To achieve this purpose, we have private _lock variable, which is set to false in the constructor.
	Of course, you should use the same ThreadSafeWriter object in every thread.
	*/
	class ThreadSafeWriter
{
public:
	/**
	Constructor
	@param file File to write messages
	*/
	ThreadSafeWriter(fstream& file);
	/**
	Writes message to a file
	@param s A message to write
	*/
	void write(const string s) const;
	/**
	Writes message to a file and ends with carriage return (endl, "\n")
	@param s A message to write
	*/
	void writeln(const string& s = "") const;
private:
	fstream& _file;
	mutable bool _lock;
	ThreadSafeWriter(const ThreadSafeWriter&);
	ThreadSafeWriter& operator= (const ThreadSafeWriter&);
};

}}}}