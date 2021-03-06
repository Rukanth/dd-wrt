/*
   Unix SMB/CIFS implementation.

   Winbind client API

   Copyright (C) Gerald (Jerry) Carter 2007


   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Required Headers */

#include "libwbclient.h"

/** @brief Convert a Windows SID to a Unix uid, allocating an uid if needed
 *
 * @param *sid        Pointer to the domain SID to be resolved
 * @param *puid       Pointer to the resolved uid_t value
 *
 * @return #wbcErr
 *
 **/

wbcErr wbcSidToUid(const struct wbcDomainSid *sid, uid_t *puid)
{
	struct winbindd_request request;
	struct winbindd_response response;
	char *sid_string = NULL;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;

	if (!sid || !puid) {
		wbc_status = WBC_ERR_INVALID_PARAM;
		BAIL_ON_WBC_ERROR(wbc_status);
	}

	/* Initialize request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	wbc_status = wbcSidToString(sid, &sid_string);
	BAIL_ON_WBC_ERROR(wbc_status);

	strncpy(request.data.sid, sid_string, sizeof(request.data.sid)-1);
	wbcFreeMemory(sid_string);

	/* Make request */

	wbc_status = wbcRequestResponse(WINBINDD_SID_TO_UID,
					&request,
					&response);
	BAIL_ON_WBC_ERROR(wbc_status);

	*puid = response.data.uid;

	wbc_status = WBC_ERR_SUCCESS;

 done:
	return wbc_status;
}

/** @brief Convert a Windows SID to a Unix uid if there already is a mapping
 *
 * @param *sid        Pointer to the domain SID to be resolved
 * @param *puid       Pointer to the resolved uid_t value
 *
 * @return #wbcErr
 *
 **/

wbcErr wbcQuerySidToUid(const struct wbcDomainSid *sid,
			uid_t *puid)
{
	return WBC_ERR_NOT_IMPLEMENTED;
}

/** @brief Convert a Unix uid to a Windows SID, allocating a SID if needed
 *
 * @param uid         Unix uid to be resolved
 * @param *sid        Pointer to the resolved domain SID
 *
 * @return #wbcErr
 *
 **/

wbcErr wbcUidToSid(uid_t uid, struct wbcDomainSid *sid)
{
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;
	struct winbindd_request request;
	struct winbindd_response response;

	if (!sid) {
		wbc_status = WBC_ERR_INVALID_PARAM;
		BAIL_ON_WBC_ERROR(wbc_status);
	}

	/* Initialize request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	request.data.uid = uid;

	/* Make request */

	wbc_status = wbcRequestResponse(WINBINDD_UID_TO_SID,
					&request,
					&response);
	BAIL_ON_WBC_ERROR(wbc_status);

	wbc_status = wbcStringToSid(response.data.sid.sid, sid);
	BAIL_ON_WBC_ERROR(wbc_status);

done:
	return wbc_status;
}

/** @brief Convert a Unix uid to a Windows SID if there already is a mapping
 *
 * @param uid         Unix uid to be resolved
 * @param *sid        Pointer to the resolved domain SID
 *
 * @return #wbcErr
 *
 **/

wbcErr wbcQueryUidToSid(uid_t uid,
			struct wbcDomainSid *sid)
{
	return WBC_ERR_NOT_IMPLEMENTED;
}

/** @brief Convert a Windows SID to a Unix gid, allocating a gid if needed
 *
 * @param *sid        Pointer to the domain SID to be resolved
 * @param *pgid       Pointer to the resolved gid_t value
 *
 * @return #wbcErr
 *
 **/

wbcErr wbcSidToGid(const struct wbcDomainSid *sid, gid_t *pgid)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;
	char *sid_string = NULL;

	if (!sid || !pgid) {
		wbc_status = WBC_ERR_INVALID_PARAM;
		BAIL_ON_WBC_ERROR(wbc_status);
	}

	/* Initialize request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	wbc_status = wbcSidToString(sid, &sid_string);
	BAIL_ON_WBC_ERROR(wbc_status);

	strncpy(request.data.sid, sid_string, sizeof(request.data.sid)-1);
	wbcFreeMemory(sid_string);

	/* Make request */

	wbc_status = wbcRequestResponse(WINBINDD_SID_TO_GID,
					&request,
					&response);
	BAIL_ON_WBC_ERROR(wbc_status);

	*pgid = response.data.gid;

	wbc_status = WBC_ERR_SUCCESS;

 done:
	return wbc_status;
}

/** @brief Convert a Windows SID to a Unix gid if there already is a mapping
 *
 * @param *sid        Pointer to the domain SID to be resolved
 * @param *pgid       Pointer to the resolved gid_t value
 *
 * @return #wbcErr
 *
 **/

wbcErr wbcQuerySidToGid(const struct wbcDomainSid *sid,
			gid_t *pgid)
{
	return WBC_ERR_NOT_IMPLEMENTED;
}

/** @brief Convert a Unix gid to a Windows SID, allocating a SID if needed
 *
 * @param gid         Unix gid to be resolved
 * @param *sid        Pointer to the resolved domain SID
 *
 * @return #wbcErr
 *
 **/

wbcErr wbcGidToSid(gid_t gid, struct wbcDomainSid *sid)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;

	if (!sid) {
		wbc_status = WBC_ERR_INVALID_PARAM;
		BAIL_ON_WBC_ERROR(wbc_status);
	}

	/* Initialize request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	request.data.gid = gid;

	/* Make request */

	wbc_status = wbcRequestResponse(WINBINDD_GID_TO_SID,
					&request,
					&response);
	BAIL_ON_WBC_ERROR(wbc_status);

	wbc_status = wbcStringToSid(response.data.sid.sid, sid);
	BAIL_ON_WBC_ERROR(wbc_status);

done:
	return wbc_status;
}

/** @brief Convert a Unix gid to a Windows SID if there already is a mapping
 *
 * @param gid         Unix gid to be resolved
 * @param *sid        Pointer to the resolved domain SID
 *
 * @return #wbcErr
 *
 **/

wbcErr wbcQueryGidToSid(gid_t gid,
			struct wbcDomainSid *sid)
{
	return WBC_ERR_NOT_IMPLEMENTED;
}

/** @brief Obtain a new uid from Winbind
 *
 * @param *puid      *pointer to the allocated uid
 *
 * @return #wbcErr
 **/

wbcErr wbcAllocateUid(uid_t *puid)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;

	if (!puid)
		return WBC_ERR_INVALID_PARAM;

	/* Initialise request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	/* Make request */

	wbc_status = wbcRequestResponse(WINBINDD_ALLOCATE_UID,
					   &request, &response);
	BAIL_ON_WBC_ERROR(wbc_status);

	/* Copy out result */
	*puid = response.data.uid;

	wbc_status = WBC_ERR_SUCCESS;

 done:
	return wbc_status;
}

/** @brief Obtain a new gid from Winbind
 *
 * @param *pgid      Pointer to the allocated gid
 *
 * @return #wbcErr
 **/

wbcErr wbcAllocateGid(gid_t *pgid)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;

	if (!pgid)
		return WBC_ERR_INVALID_PARAM;

	/* Initialise request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	/* Make request */

	wbc_status = wbcRequestResponse(WINBINDD_ALLOCATE_GID,
					   &request, &response);
	BAIL_ON_WBC_ERROR(wbc_status);

	/* Copy out result */
	*pgid = response.data.gid;

	wbc_status = WBC_ERR_SUCCESS;

 done:
	return wbc_status;
}

/* we can't include smb.h here... */
#define _ID_TYPE_UID 1
#define _ID_TYPE_GID 2

/** @brief Set an user id mapping
 *
 * @param uid       Uid of the desired mapping.
 * @param *sid      Pointer to the sid of the diresired mapping.
 *
 * @return #wbcErr
 **/
wbcErr wbcSetUidMapping(uid_t uid, const struct wbcDomainSid *sid)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;
	char *sid_string = NULL;

	if (!sid) {
		return WBC_ERR_INVALID_PARAM;
	}

	/* Initialise request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	/* Make request */

	request.data.dual_idmapset.id = uid;
	request.data.dual_idmapset.type = _ID_TYPE_UID;

	wbc_status = wbcSidToString(sid, &sid_string);
	BAIL_ON_WBC_ERROR(wbc_status);

	strncpy(request.data.dual_idmapset.sid, sid_string,
		sizeof(request.data.dual_idmapset.sid)-1);
	wbcFreeMemory(sid_string);

	wbc_status = wbcRequestResponse(WINBINDD_SET_MAPPING,
					&request, &response);
	BAIL_ON_WBC_ERROR(wbc_status);

 done:
	return wbc_status;
}

/** @brief Set a group id mapping
 *
 * @param gid       Gid of the desired mapping.
 * @param *sid      Pointer to the sid of the diresired mapping.
 *
 * @return #wbcErr
 **/
wbcErr wbcSetGidMapping(gid_t gid, const struct wbcDomainSid *sid)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;
	char *sid_string = NULL;

	if (!sid) {
		return WBC_ERR_INVALID_PARAM;
	}

	/* Initialise request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	/* Make request */

	request.data.dual_idmapset.id = gid;
	request.data.dual_idmapset.type = _ID_TYPE_GID;

	wbc_status = wbcSidToString(sid, &sid_string);
	BAIL_ON_WBC_ERROR(wbc_status);

	strncpy(request.data.dual_idmapset.sid, sid_string,
		sizeof(request.data.dual_idmapset.sid)-1);
	wbcFreeMemory(sid_string);

	wbc_status = wbcRequestResponse(WINBINDD_SET_MAPPING,
					&request, &response);
	BAIL_ON_WBC_ERROR(wbc_status);

 done:
	return wbc_status;
}

/** @brief Remove a user id mapping
 *
 * @param uid       Uid of the mapping to remove.
 * @param *sid      Pointer to the sid of the mapping to remove.
 *
 * @return #wbcErr
 **/
wbcErr wbcRemoveUidMapping(uid_t uid, const struct wbcDomainSid *sid)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;
	char *sid_string = NULL;

	if (!sid) {
		return WBC_ERR_INVALID_PARAM;
	}

	/* Initialise request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	/* Make request */

	request.data.dual_idmapset.id = uid;
	request.data.dual_idmapset.type = _ID_TYPE_UID;

	wbc_status = wbcSidToString(sid, &sid_string);
	BAIL_ON_WBC_ERROR(wbc_status);

	strncpy(request.data.dual_idmapset.sid, sid_string,
		sizeof(request.data.dual_idmapset.sid)-1);
	wbcFreeMemory(sid_string);

	wbc_status = wbcRequestResponse(WINBINDD_REMOVE_MAPPING,
					&request, &response);
	BAIL_ON_WBC_ERROR(wbc_status);

 done:
	return wbc_status;
}

/** @brief Remove a group id mapping
 *
 * @param gid       Gid of the mapping to remove.
 * @param *sid      Pointer to the sid of the mapping to remove.
 *
 * @return #wbcErr
 **/
wbcErr wbcRemoveGidMapping(gid_t gid, const struct wbcDomainSid *sid)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;
	char *sid_string = NULL;

	if (!sid) {
		return WBC_ERR_INVALID_PARAM;
	}

	/* Initialise request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	/* Make request */

	request.data.dual_idmapset.id = gid;
	request.data.dual_idmapset.type = _ID_TYPE_GID;

	wbc_status = wbcSidToString(sid, &sid_string);
	BAIL_ON_WBC_ERROR(wbc_status);

	strncpy(request.data.dual_idmapset.sid, sid_string,
		sizeof(request.data.dual_idmapset.sid)-1);
	wbcFreeMemory(sid_string);

	wbc_status = wbcRequestResponse(WINBINDD_REMOVE_MAPPING,
					&request, &response);
	BAIL_ON_WBC_ERROR(wbc_status);

 done:
	return wbc_status;
}

/** @brief Set the highwater mark for allocated uids.
 *
 * @param uid_hwm      The new uid highwater mark value
 *
 * @return #wbcErr
 **/
wbcErr wbcSetUidHwm(uid_t uid_hwm)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;

	/* Initialise request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	/* Make request */

	request.data.dual_idmapset.id = uid_hwm;
	request.data.dual_idmapset.type = _ID_TYPE_UID;

	wbc_status = wbcRequestResponse(WINBINDD_SET_HWM,
					&request, &response);
	BAIL_ON_WBC_ERROR(wbc_status);

 done:
	return wbc_status;
}

/** @brief Set the highwater mark for allocated gids.
 *
 * @param gid_hwm      The new gid highwater mark value
 *
 * @return #wbcErr
 **/
wbcErr wbcSetGidHwm(gid_t gid_hwm)
{
	struct winbindd_request request;
	struct winbindd_response response;
	wbcErr wbc_status = WBC_ERR_UNKNOWN_FAILURE;

	/* Initialise request */

	ZERO_STRUCT(request);
	ZERO_STRUCT(response);

	/* Make request */

	request.data.dual_idmapset.id = gid_hwm;
	request.data.dual_idmapset.type = _ID_TYPE_GID;

	wbc_status = wbcRequestResponse(WINBINDD_SET_HWM,
					&request, &response);
	BAIL_ON_WBC_ERROR(wbc_status);

 done:
	return wbc_status;
}
