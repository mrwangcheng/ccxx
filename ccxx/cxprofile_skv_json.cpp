#include "cxprofile_skv_json.h"


#include "cxrapidjson.h"


using namespace std;


CxSkverJson::CxSkverJson() :
    CxSkverBase()
{
}

CxSkverJson::CxSkverJson(const std::map<std::string, std::map<std::string, std::string> > & sectionEntryValues) :
    CxSkverBase(sectionEntryValues)
{
}

CxSkverJson::CxSkverJson( const std::string & sFilePath ) :
    CxSkverBase()
{
    load(sFilePath);
}

CxSkverJson::~CxSkverJson()
{
}

bool CxSkverJson::loadImpl(std::map<string, std::map<string, string> > &sectionEntryValues, const string &sFilePath)
{
    CxRapidJson::loadTable(sFilePath, sectionEntryValues);
    return sectionEntryValues.size()>0;
}

bool CxSkverJson::saveImpl(const std::map<string, std::map<string, string> > &sectionEntryValues, const string &sFilePath, bool bRenew) const
{
    return CxRapidJson::saveTable(sFilePath, sectionEntryValues, "", 1) > 0;
}
