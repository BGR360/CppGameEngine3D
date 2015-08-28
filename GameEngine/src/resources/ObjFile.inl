bool ObjFile::isOpen() const
{
	return m_bIsOpen;
}

bool ObjFile::hasTextureCoordinates() const
{
	return m_bHasVt;
}

bool ObjFile::hasNormals() const
{
	return m_bHasVn;
}

uint ObjFile::getNumLines() const
{
	if (m_bIsOpen)
	{
		return m_lineNumber;
	}
}

uint ObjFile::getFileSize() const
{
	return m_fileSize;
}

float ObjFile::getLinesPerByte() const
{
	return getNumLines() / (float)getFileSize();
}

vector<Vector3>& ObjFile::get_v_list()
{
	return m_v_list;
}

vector<Vector2>& ObjFile::get_vt_list()
{
	return m_vt_list;
}

vector<Vector3>& ObjFile::get_vn_list()
{
	return m_vn_list;
}

vector<ObjVertex>& ObjFile::getVertices()
{
	return m_objVertices;
}

vector<uint>& ObjFile::getIndices()
{
	return m_indices;
}

uint ObjVertex::hash()
{
	uint h = 0;
	uint highorder = h & 0xf8000000;
	h = h << 5;
	h = h ^ (highorder >> 27);
	h = h ^ v_index;

	highorder = h & 0xf8000000;
	h = h << 5;
	h = h ^ (highorder >> 27);
	h = h ^ vt_index;

	highorder = h & 0xf8000000;
	h = h << 5;
	h = h ^ (highorder >> 27);
	h = h ^ vn_index;

	return h;
}