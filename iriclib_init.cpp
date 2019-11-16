#include "error_macros.h"
#include "h5cgnsfile.h"
#include "h5cgnsfilesolutionwriter.h"
#include "iriclib.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_h5cgnsfiles.h"
#include "internal/iric_logger.h"

#include <Poco/File.h>

#include <sstream>

using namespace iRICLib;

namespace {

H5CgnsFileSolutionWriter::Mode writerMode = H5CgnsFileSolutionWriter::Mode::Standard;

int _checkFileIsOpen(int fid)
{
	H5CgnsFile* file;

	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	if (file == nullptr) {
		return IRIC_INVALID_FILEID;
	}

	return IRIC_NO_ERROR;
}


} // namespace

int cg_iRIC_Open(const char* filename, int mode, int* fid)
{
	_iric_logger_init();

	H5CgnsFile::Mode m = H5CgnsFile::Mode::OpenReadOnly;

	if (mode == IRIC_MODE_WRITE) {
		m = H5CgnsFile::Mode::Create;
	} else if (mode == IRIC_MODE_MODIFY) {
		m = H5CgnsFile::Mode::OpenModify;
	}

	try {
		auto f = new H5CgnsFile(filename, m);
		f->setWriterMode(writerMode);

		int ier = _iric_h5cgnsfiles_register(f, fid);
		RETURN_IF_ERR;

		return IRIC_NO_ERROR;
	}  catch (...) {
		std::ostringstream ss;
		ss << "In cg_iRIC_Open(), opening " << filename << " failed";
		_iric_logger_error(ss.str());
		return IRIC_H5_OPEN_FAIL;
	}
}

int cg_iRIC_Close(int fid)
{
	return _iric_h5cgnsfiles_unregister(fid);
}

int cg_iRIC_Init(int fid)
{
	return _checkFileIsOpen(fid);
}

int cg_iRIC_InitRead(int fid)
{
	return _checkFileIsOpen(fid);
}

int iRIC_InitOption(int option)
{
	if (option == IRIC_OPTION_CANCEL) {
		try {
			Poco::File f(".cancel_ok");
			f.createFile();
			return IRIC_NO_ERROR;
		} catch (...) {
			std::ostringstream ss;
			ss << "Creating .cancel_ok failed";
			_iric_logger_error(ss.str());
		}
	} else if (option == IRIC_OPTION_DIVIDESOLUTIONS) {
		writerMode = H5CgnsFileSolutionWriter::Mode::Separate;
		return IRIC_NO_ERROR;
	} else if (option == IRIC_OPTION_STDSOLUTION) {
		writerMode = H5CgnsFileSolutionWriter::Mode::Standard;
		return IRIC_NO_ERROR;
	}

	return IRIC_NO_ERROR;
}

int cg_iRIC_Flush(const char* /*name*/, int fid)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	return file->flush();
}

int cg_iRIC_GotoBase(int fid, int* /*B*/)
{
	return _checkFileIsOpen(fid);
}

int cg_iRIC_GotoCC(int fid)
{
	return _checkFileIsOpen(fid);
}

int cg_iRIC_GotoRawDataTop(int fid)
{
	return _checkFileIsOpen(fid);
}
