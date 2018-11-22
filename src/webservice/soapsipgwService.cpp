/* soapsipgwService.cpp
   Generated by gSOAP 2.8.70 for webservice_source.h

gSOAP XML Web services tools
Copyright (C) 2000-2018, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapsipgwService.h"

sipgwService::sipgwService()
{	this->soap = soap_new();
	this->soap_own = true;
	sipgwService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

sipgwService::sipgwService(const sipgwService& rhs)
{	this->soap = rhs.soap;
	this->soap_own = false;
}

sipgwService::sipgwService(struct soap *_soap)
{	this->soap = _soap;
	this->soap_own = false;
	sipgwService_init(_soap->imode, _soap->omode);
}

sipgwService::sipgwService(soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	sipgwService_init(iomode, iomode);
}

sipgwService::sipgwService(soap_mode imode, soap_mode omode)
{	this->soap = soap_new();
	this->soap_own = true;
	sipgwService_init(imode, omode);
}

sipgwService::~sipgwService()
{	if (this->soap_own)
		soap_free(this->soap);
}

void sipgwService::sipgwService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this->soap, imode);
	soap_omode(this->soap, omode);
	static const struct Namespace namespaces[] = {
        {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
        {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
        {"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
        {"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
        {"ns2", "urn:sipgw", NULL, NULL},
        {NULL, NULL, NULL, NULL}
    };
	soap_set_namespaces(this->soap, namespaces);
}

void sipgwService::destroy()
{	soap_destroy(this->soap);
	soap_end(this->soap);
}

void sipgwService::reset()
{	this->destroy();
	soap_done(this->soap);
	soap_initialize(this->soap);
	sipgwService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
sipgwService *sipgwService::copy()
{	sipgwService *dup = SOAP_NEW_UNMANAGED(sipgwService);
	if (dup)
	{	soap_done(dup->soap);
		soap_copy_context(dup->soap, this->soap);
	}
	return dup;
}
#endif

sipgwService& sipgwService::operator=(const sipgwService& rhs)
{	if (this->soap != rhs.soap)
	{	if (this->soap_own)
			soap_free(this->soap);
		this->soap = rhs.soap;
		this->soap_own = false;
	}
	return *this;
}

int sipgwService::soap_close_socket()
{	return soap_closesock(this->soap);
}

int sipgwService::soap_force_close_socket()
{	return soap_force_closesock(this->soap);
}

int sipgwService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this->soap, string, detailXML);
}

int sipgwService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

int sipgwService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this->soap, string, detailXML);
}

int sipgwService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

void sipgwService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this->soap, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void sipgwService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this->soap, os);
}
#endif

char *sipgwService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this->soap, buf, len);
}
#endif

void sipgwService::soap_noheader()
{	this->soap->header = NULL;
}

::SOAP_ENV__Header *sipgwService::soap_header()
{	return this->soap->header;
}

#ifndef WITH_NOIO
int sipgwService::run(int port)
{	if (!soap_valid_socket(this->soap->master) && !soap_valid_socket(this->bind(NULL, port, 100)))
		return this->soap->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->soap->errnum == 0) // timeout?
				this->soap->error = SOAP_OK;
			break;
		}
		if (this->serve())
			break;
		this->destroy();
	}
	return this->soap->error;
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int sipgwService::ssl_run(int port)
{	if (!soap_valid_socket(this->soap->master) && !soap_valid_socket(this->bind(NULL, port, 100)))
		return this->soap->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->soap->errnum == 0) // timeout?
				this->soap->error = SOAP_OK;
			break;
		}
		if (this->ssl_accept() || this->serve())
			break;
		this->destroy();
	}
	return this->soap->error;
}
#endif

SOAP_SOCKET sipgwService::bind(const char *host, int port, int backlog)
{	return soap_bind(this->soap, host, port, backlog);
}

SOAP_SOCKET sipgwService::accept()
{	return soap_accept(this->soap);
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int sipgwService::ssl_accept()
{	return soap_ssl_accept(this->soap);
}
#endif
#endif

int sipgwService::serve()
{
#ifndef WITH_FASTCGI
	this->soap->keep_alive = this->soap->max_keep_alive + 1;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (this->soap->keep_alive > 0 && this->soap->max_keep_alive > 0)
			this->soap->keep_alive--;
#endif
		if (soap_begin_serve(this->soap))
		{	if (this->soap->error >= SOAP_STOP)
				continue;
			return this->soap->error;
		}
		if ((dispatch() || (this->soap->fserveloop && this->soap->fserveloop(this->soap))) && this->soap->error && this->soap->error < SOAP_STOP)
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this->soap);
#else
			return soap_send_fault(this->soap);
#endif
		}
#ifdef WITH_FASTCGI
		soap_destroy(this->soap);
		soap_end(this->soap);
	} while (1);
#else
	} while (this->soap->keep_alive);
#endif
	return SOAP_OK;
}

static int serve_ns2__login(struct soap*, sipgwService*);
static int serve_ns2__logout(struct soap*, sipgwService*);
static int serve_ns2__keepalive(struct soap*, sipgwService*);
static int serve_ns2__get_directory_info(struct soap*, sipgwService*);
static int serve_ns2__ptz_control(struct soap*, sipgwService*);
static int serve_ns2__start_real_play(struct soap*, sipgwService*);
static int serve_ns2__stop_real_play(struct soap*, sipgwService*);
static int serve_ns2__start_play_back(struct soap*, sipgwService*);
static int serve_ns2__stop_play_back(struct soap*, sipgwService*);
static int serve_ns2__call_lookup(struct soap*, sipgwService*);

int sipgwService::dispatch()
{	return dispatch(this->soap);
}

int sipgwService::dispatch(struct soap* soap)
{
	sipgwService_init(soap->imode, soap->omode);

	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "ns2:login"))
		return serve_ns2__login(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns2:logout"))
		return serve_ns2__logout(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns2:keepalive"))
		return serve_ns2__keepalive(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns2:get-directory-info"))
		return serve_ns2__get_directory_info(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns2:ptz-control"))
		return serve_ns2__ptz_control(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns2:start-real-play"))
		return serve_ns2__start_real_play(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns2:stop-real-play"))
		return serve_ns2__stop_real_play(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns2:start-play-back"))
		return serve_ns2__start_play_back(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns2:stop-play-back"))
		return serve_ns2__stop_play_back(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns2:call-lookup"))
		return serve_ns2__call_lookup(soap, this);
	return soap->error = SOAP_NO_METHOD;
}

static int serve_ns2__login(struct soap *soap, sipgwService *service)
{	struct ns2__login soap_tmp_ns2__login;
	struct ns2__loginResponse soap_tmp_ns2__loginResponse;
	char * soap_tmp_string;
	soap_default_ns2__loginResponse(soap, &soap_tmp_ns2__loginResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__loginResponse.result = &soap_tmp_string;
	soap_default_ns2__login(soap, &soap_tmp_ns2__login);
	if (!soap_get_ns2__login(soap, &soap_tmp_ns2__login, "ns2:login", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->login(soap_tmp_ns2__login.user_id, soap_tmp_ns2__login.password, soap_tmp_ns2__loginResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__loginResponse(soap, &soap_tmp_ns2__loginResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__loginResponse(soap, &soap_tmp_ns2__loginResponse, "ns2:loginResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__loginResponse(soap, &soap_tmp_ns2__loginResponse, "ns2:loginResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns2__logout(struct soap *soap, sipgwService *service)
{	struct ns2__logout soap_tmp_ns2__logout;
	struct ns2__logoutResponse soap_tmp_ns2__logoutResponse;
	char * soap_tmp_string;
	soap_default_ns2__logoutResponse(soap, &soap_tmp_ns2__logoutResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__logoutResponse.result = &soap_tmp_string;
	soap_default_ns2__logout(soap, &soap_tmp_ns2__logout);
	if (!soap_get_ns2__logout(soap, &soap_tmp_ns2__logout, "ns2:logout", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->logout(soap_tmp_ns2__logout.user_id, soap_tmp_ns2__logout.password, soap_tmp_ns2__logoutResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__logoutResponse(soap, &soap_tmp_ns2__logoutResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__logoutResponse(soap, &soap_tmp_ns2__logoutResponse, "ns2:logoutResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__logoutResponse(soap, &soap_tmp_ns2__logoutResponse, "ns2:logoutResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns2__keepalive(struct soap *soap, sipgwService *service)
{	struct ns2__keepalive soap_tmp_ns2__keepalive;
	struct ns2__keepaliveResponse soap_tmp_ns2__keepaliveResponse;
	char * soap_tmp_string;
	soap_default_ns2__keepaliveResponse(soap, &soap_tmp_ns2__keepaliveResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__keepaliveResponse.result = &soap_tmp_string;
	soap_default_ns2__keepalive(soap, &soap_tmp_ns2__keepalive);
	if (!soap_get_ns2__keepalive(soap, &soap_tmp_ns2__keepalive, "ns2:keepalive", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->keepalive(soap_tmp_ns2__keepalive.user_id, soap_tmp_ns2__keepalive.password, soap_tmp_ns2__keepaliveResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__keepaliveResponse(soap, &soap_tmp_ns2__keepaliveResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__keepaliveResponse(soap, &soap_tmp_ns2__keepaliveResponse, "ns2:keepaliveResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__keepaliveResponse(soap, &soap_tmp_ns2__keepaliveResponse, "ns2:keepaliveResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns2__get_directory_info(struct soap *soap, sipgwService *service)
{	struct ns2__get_directory_info soap_tmp_ns2__get_directory_info;
	struct ns2__get_directory_infoResponse soap_tmp_ns2__get_directory_infoResponse;
	char * soap_tmp_string;
	soap_default_ns2__get_directory_infoResponse(soap, &soap_tmp_ns2__get_directory_infoResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__get_directory_infoResponse.directory_info_buf_out = &soap_tmp_string;
	soap_default_ns2__get_directory_info(soap, &soap_tmp_ns2__get_directory_info);
	if (!soap_get_ns2__get_directory_info(soap, &soap_tmp_ns2__get_directory_info, "ns2:get-directory-info", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->get_directory_info(soap_tmp_ns2__get_directory_info.target_dev_id, soap_tmp_ns2__get_directory_info.target_realm, soap_tmp_ns2__get_directory_infoResponse.directory_info_buf_out);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__get_directory_infoResponse(soap, &soap_tmp_ns2__get_directory_infoResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__get_directory_infoResponse(soap, &soap_tmp_ns2__get_directory_infoResponse, "ns2:get-directory-infoResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__get_directory_infoResponse(soap, &soap_tmp_ns2__get_directory_infoResponse, "ns2:get-directory-infoResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns2__ptz_control(struct soap *soap, sipgwService *service)
{	struct ns2__ptz_control soap_tmp_ns2__ptz_control;
	struct ns2__ptz_controlResponse soap_tmp_ns2__ptz_controlResponse;
	char * soap_tmp_string;
	soap_default_ns2__ptz_controlResponse(soap, &soap_tmp_ns2__ptz_controlResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__ptz_controlResponse.result = &soap_tmp_string;
	soap_default_ns2__ptz_control(soap, &soap_tmp_ns2__ptz_control);
	if (!soap_get_ns2__ptz_control(soap, &soap_tmp_ns2__ptz_control, "ns2:ptz-control", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->ptz_control(soap_tmp_ns2__ptz_control.target_dev_id, soap_tmp_ns2__ptz_control.target_realm, soap_tmp_ns2__ptz_control.ptz, soap_tmp_ns2__ptz_control.ptz_speed, soap_tmp_ns2__ptz_controlResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__ptz_controlResponse(soap, &soap_tmp_ns2__ptz_controlResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__ptz_controlResponse(soap, &soap_tmp_ns2__ptz_controlResponse, "ns2:ptz-controlResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__ptz_controlResponse(soap, &soap_tmp_ns2__ptz_controlResponse, "ns2:ptz-controlResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns2__start_real_play(struct soap *soap, sipgwService *service)
{	struct ns2__start_real_play soap_tmp_ns2__start_real_play;
	struct ns2__start_real_playResponse soap_tmp_ns2__start_real_playResponse;
	char * soap_tmp_string;
	soap_default_ns2__start_real_playResponse(soap, &soap_tmp_ns2__start_real_playResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__start_real_playResponse.call_id = &soap_tmp_string;
	soap_default_ns2__start_real_play(soap, &soap_tmp_ns2__start_real_play);
	if (!soap_get_ns2__start_real_play(soap, &soap_tmp_ns2__start_real_play, "ns2:start-real-play", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->start_real_play(soap_tmp_ns2__start_real_play.user_id, soap_tmp_ns2__start_real_play.target_dev_id, soap_tmp_ns2__start_real_play.target_realm, soap_tmp_ns2__start_real_play.media_recv_ip, soap_tmp_ns2__start_real_play.media_recv_port, soap_tmp_ns2__start_real_playResponse.call_id);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__start_real_playResponse(soap, &soap_tmp_ns2__start_real_playResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__start_real_playResponse(soap, &soap_tmp_ns2__start_real_playResponse, "ns2:start-real-playResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__start_real_playResponse(soap, &soap_tmp_ns2__start_real_playResponse, "ns2:start-real-playResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns2__stop_real_play(struct soap *soap, sipgwService *service)
{	struct ns2__stop_real_play soap_tmp_ns2__stop_real_play;
	struct ns2__stop_real_playResponse soap_tmp_ns2__stop_real_playResponse;
	char * soap_tmp_string;
	soap_default_ns2__stop_real_playResponse(soap, &soap_tmp_ns2__stop_real_playResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__stop_real_playResponse.result = &soap_tmp_string;
	soap_default_ns2__stop_real_play(soap, &soap_tmp_ns2__stop_real_play);
	if (!soap_get_ns2__stop_real_play(soap, &soap_tmp_ns2__stop_real_play, "ns2:stop-real-play", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->stop_real_play(soap_tmp_ns2__stop_real_play.user_id, soap_tmp_ns2__stop_real_play.call_id, soap_tmp_ns2__stop_real_playResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__stop_real_playResponse(soap, &soap_tmp_ns2__stop_real_playResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__stop_real_playResponse(soap, &soap_tmp_ns2__stop_real_playResponse, "ns2:stop-real-playResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__stop_real_playResponse(soap, &soap_tmp_ns2__stop_real_playResponse, "ns2:stop-real-playResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns2__start_play_back(struct soap *soap, sipgwService *service)
{	struct ns2__start_play_back soap_tmp_ns2__start_play_back;
	struct ns2__start_play_backResponse soap_tmp_ns2__start_play_backResponse;
	char * soap_tmp_string;
	soap_default_ns2__start_play_backResponse(soap, &soap_tmp_ns2__start_play_backResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__start_play_backResponse.call_id = &soap_tmp_string;
	soap_default_ns2__start_play_back(soap, &soap_tmp_ns2__start_play_back);
	if (!soap_get_ns2__start_play_back(soap, &soap_tmp_ns2__start_play_back, "ns2:start-play-back", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->start_play_back(soap_tmp_ns2__start_play_back.user_id, soap_tmp_ns2__start_play_back.target_dev_id, soap_tmp_ns2__start_play_back.target_realm, soap_tmp_ns2__start_play_back.media_recv_ip, soap_tmp_ns2__start_play_back.media_recv_port, soap_tmp_ns2__start_play_back.start_time, soap_tmp_ns2__start_play_back.end_time, soap_tmp_ns2__start_play_backResponse.call_id);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__start_play_backResponse(soap, &soap_tmp_ns2__start_play_backResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__start_play_backResponse(soap, &soap_tmp_ns2__start_play_backResponse, "ns2:start-play-backResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__start_play_backResponse(soap, &soap_tmp_ns2__start_play_backResponse, "ns2:start-play-backResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns2__stop_play_back(struct soap *soap, sipgwService *service)
{	struct ns2__stop_play_back soap_tmp_ns2__stop_play_back;
	struct ns2__stop_play_backResponse soap_tmp_ns2__stop_play_backResponse;
	char * soap_tmp_string;
	soap_default_ns2__stop_play_backResponse(soap, &soap_tmp_ns2__stop_play_backResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__stop_play_backResponse.result = &soap_tmp_string;
	soap_default_ns2__stop_play_back(soap, &soap_tmp_ns2__stop_play_back);
	if (!soap_get_ns2__stop_play_back(soap, &soap_tmp_ns2__stop_play_back, "ns2:stop-play-back", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->stop_play_back(soap_tmp_ns2__stop_play_back.user_id, soap_tmp_ns2__stop_play_back.call_id, soap_tmp_ns2__stop_play_backResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__stop_play_backResponse(soap, &soap_tmp_ns2__stop_play_backResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__stop_play_backResponse(soap, &soap_tmp_ns2__stop_play_backResponse, "ns2:stop-play-backResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__stop_play_backResponse(soap, &soap_tmp_ns2__stop_play_backResponse, "ns2:stop-play-backResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve_ns2__call_lookup(struct soap *soap, sipgwService *service)
{	struct ns2__call_lookup soap_tmp_ns2__call_lookup;
	struct ns2__call_lookupResponse soap_tmp_ns2__call_lookupResponse;
	char * soap_tmp_string;
	soap_default_ns2__call_lookupResponse(soap, &soap_tmp_ns2__call_lookupResponse);
	soap_tmp_string = NULL;
	soap_tmp_ns2__call_lookupResponse.result = &soap_tmp_string;
	soap_default_ns2__call_lookup(soap, &soap_tmp_ns2__call_lookup);
	if (!soap_get_ns2__call_lookup(soap, &soap_tmp_ns2__call_lookup, "ns2:call-lookup", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->call_lookup(soap_tmp_ns2__call_lookup.user_id, soap_tmp_ns2__call_lookupResponse.result);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_ns2__call_lookupResponse(soap, &soap_tmp_ns2__call_lookupResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns2__call_lookupResponse(soap, &soap_tmp_ns2__call_lookupResponse, "ns2:call-lookupResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns2__call_lookupResponse(soap, &soap_tmp_ns2__call_lookupResponse, "ns2:call-lookupResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */
