#pragma once

// from
// https://github.com/OmniBlade/LasMarionetas/blob/master/src/framework/gz/igzfile.h

/// ??? It seems that in "Edith 666", cIGZString just did not exist yet.
/// Instead, cRZString derives from the HP STL's basic_string<char>...
// class cIGZString;
class cRZString;

class cIGZFile {
public:
  enum {
    kCreateModeCreateNew,
    kCreateModeCreateAlways,
    kCreateModeOpenExisting,
    kCreateModeOpenAlways,
    kCreateModeTruncateExisting
  };

  virtual bool Open(int iOpenMode, int iCreateMode, int iShareMode) = 0;

  virtual bool IsOpen() const = 0;

  virtual bool Close() = 0;

  virtual int Position() = 0;

  virtual unsigned int Length() = 0;

  virtual bool SetLength(unsigned int uiLength) = 0;

  virtual unsigned int SeekToBegin() = 0;

  virtual unsigned int SeekToEnd() = 0;

  virtual unsigned int SeekToRelativePosition(int iPos) = 0;

  virtual unsigned int SeekToExactPosition(int iPos) = 0;

  virtual unsigned int Seek(int iPos, int iWhence) = 0;

  virtual bool Read(void *pDst, unsigned int uiLength) = 0;

  virtual bool ReadWithCount(void *pDst, unsigned int &ruiLength) = 0;

  virtual bool Write(const void *pSrc, unsigned int uiLength) = 0;

  virtual bool WriteWithCount(void *pSrc, unsigned int &ruiLength) = 0;

  virtual bool Flush() = 0;

  virtual bool Remove() = 0;

  virtual bool Rename(const cRZString *pName) = 0;

  virtual bool Exists() = 0;

  virtual bool Copy(const cIGZFile *pDst, bool bOverwriteExisting) = 0;

  virtual bool Copy(const cRZString *pDst, bool bOverwriteExisting) = 0;

  virtual const cRZString &GetPath() const = 0;

  virtual const cRZString &GetPath(cRZString &rPath) const = 0;

  virtual const char *GetPathCStr() const = 0;

  virtual const cRZString &SetPath(const char *szPath) = 0;

  virtual const cRZString &SetPath(const cRZString &crPath) = 0;

  virtual ~cIGZFile();

  virtual unsigned int AddRef() = 0;

  virtual unsigned int Release() = 0;
};
