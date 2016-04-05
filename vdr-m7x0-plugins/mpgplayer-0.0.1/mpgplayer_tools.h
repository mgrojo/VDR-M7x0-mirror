/*
 *
 * See the README file for copyright information and how to reach the author.
 *
 * 
 */

#ifndef __MPGPLAYER_TOOLS_H
#define __MPGPLAYER_TOOLS_H
#include <vdr/tools.h>
#include <sys/types.h>
#include <regex.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

inline bool FileReadable(const char *file)
{
  while (access(file, R_OK) < 0) {
        if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
           return false;

        if (FATALERRNO) {
           LOG_ERROR;
           return false;
           }
        }
   return true;
}

inline bool FileStat64(const char *file, struct stat64 *st)
{
  while (stat64(file, st) < 0) {
        if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
           return false;

        if (FATALERRNO) {
           LOG_ERROR;
           return false;
           }
        }
  return true;
}

inline bool FileLStat64(const char *file, struct stat64 *st)
{
  while (lstat64(file, st) < 0) {
        if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
           return false;

        if (FATALERRNO) {
           LOG_ERROR;
           return false;
           }
        }
  return true;
}


inline bool FileStat(const char *file, struct stat *st)
{
  while (stat(file, st) < 0) {
        if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
           return false;

        if (FATALERRNO) {
           LOG_ERROR;
           return false;
           }
        }
  return true;
}

void MergeSort(void **List, int Count,
               int (*Compare)(const void *, const void *));

class cPathObject : public cListObject {
private:
  char *name;
  char *linkTo;
  bool isDir;
  int cmpLength;
public:
  cPathObject(const char *Name, const char *LinkTo = NULL, bool IsDir = false) {
     name = strdup(Name);
     if (LinkTo)
        linkTo = strdup(LinkTo);
     else
        linkTo = NULL;
     isDir = IsDir;
     cmpLength = 0;
     }
  virtual ~cPathObject() { free(name); if (linkTo) free(linkTo); }
  const char *Name(void) const { return name; }
  const char *LinkTo(void) const { return linkTo; }
  bool IsDir(void) const { return isDir; }
  void SetCompareLength(int l) { cmpLength = l; }
  virtual int Compare(const cListObject &ListObject) const {
    cPathObject *pathObj = (cPathObject *) &ListObject;
    if (!name || !pathObj->name) {
       esyslog("ERROR: PathObject without name!!");
       return -1;
       }

    if (!cmpLength && !pathObj->cmpLength) {
       return strcoll(name, pathObj->name);
       }

    return (cmpLength == pathObj->cmpLength ?
            strncmp(name, pathObj->name, cmpLength) :
            cmpLength - pathObj->cmpLength);
    }
  };

class cDirScanner {
private:
  char *curPath;
  char *basePath;
  cList<cPathObject> fileList;
  cList<cPathObject> dirList;
  bool readOkay;
  bool readHidden;
  bool sortDirs;
  bool sortFiles;
  regex_t *fileMatch;

  bool ReadDir(void);
public:
  cDirScanner(const char *BasePath, const char *InitPath, const char *RegexFiles, bool ReadHidden);
  ~cDirScanner();
  bool Exists(const char *Path) const;
  void Clear(void);
  bool ChDir(const char *Path);
  bool Read(void);
  const char *DisplayPath(void) const;
  const char *Path(void) const { return curPath; }
  const cList<cPathObject> *DirList() const { return &dirList; }
  const cList<cPathObject> *FileList() const { return &fileList; }
  cList<cPathObject> *MutableFileList() { return &fileList; }
  bool IsRead(void) const { return readOkay; }
  bool SetBasePath(const char *Path);
  const char *GetBasePath(void) { return basePath; }
  void SetReadHidden(bool ReadHidden) {
      if (readHidden != ReadHidden) {
         readHidden = ReadHidden;
         readOkay= false;
         }
      }
  };

class cReadDir64 {
private:
  DIR *directory;
  struct dirent64 *result;
  union { // according to "The GNU C Library Reference Manual"
    struct dirent64 d;
    char b[offsetof(struct dirent64, d_name) + NAME_MAX + 1];
    } u;
public:
  cReadDir64(const char *Directory);
  ~cReadDir64();
  bool Ok(void) { return directory != NULL; }
  struct dirent64 *Next(void);
  };


/// cMpgUnbufferedFile is used for large files that are mainly written or read
/// in a streaming manner, and thus should not be cached.

class cMpgUnbufferedFile {
private:
  int fd;
  off64_t curpos;
  off64_t cachedstart;
  off64_t cachedend;
  off64_t begin;
  off64_t lastpos;
  off64_t ahead;
  size_t readahead;
  size_t written;
  size_t totwritten;
  int FadviseDrop(off64_t Offset, off_t Len);
//M7X0 BEGIN AK
#ifdef USE_DIRECT_IO
  bool directIOused;
  int blockSize;
  int FallBackFromDirectIO(void);
#endif
//M7X0 END AK
public:
  cMpgUnbufferedFile(void);
  ~cMpgUnbufferedFile();
  int Open(const char *FileName, int Flags, mode_t Mode = DEFFILEMODE);
  int Close(void);
  off64_t Seek(off64_t Offset, int Whence);
  ssize_t Read(void *Data, size_t Size);
  static cMpgUnbufferedFile *Create(const char *FileName, int Flags, mode_t Mode = DEFFILEMODE);
  };

int CloseMpgVideoFile(cMpgUnbufferedFile *File);
#endif
