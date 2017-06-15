#ifndef D_AsarBuildTime_H
#define D_AsarBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  AsarBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class AsarBuildTime
  {
  public:
    explicit AsarBuildTime();
    virtual ~AsarBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    AsarBuildTime(const AsarBuildTime&);
    AsarBuildTime& operator=(const AsarBuildTime&);

  };

#endif  // D_AsarBuildTime_H
