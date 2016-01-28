# -*- coding: utf-8 -*-

###############################################################################
#
# StoreToken
# Stores a token.
#
# Python versions 2.6, 2.7, 3.x
#
# Copyright 2014, Temboo Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
# either express or implied. See the License for the specific
# language governing permissions and limitations under the License.
#
#
###############################################################################

from temboo.core.choreography import Choreography
from temboo.core.choreography import InputSet
from temboo.core.choreography import ResultSet
from temboo.core.choreography import ChoreographyExecution

import json

class StoreToken(Choreography):

    def __init__(self, temboo_session):
        """
        Create a new instance of the StoreToken Choreo. A TembooSession object, containing a valid
        set of Temboo credentials, must be supplied.
        """
        super(StoreToken, self).__init__(temboo_session, '/Library/Utilities/TokenStorage/StoreToken')


    def new_input_set(self):
        return StoreTokenInputSet()

    def _make_result_set(self, result, path):
        return StoreTokenResultSet(result, path)

    def _make_execution(self, session, exec_id, path):
        return StoreTokenChoreographyExecution(session, exec_id, path)

class StoreTokenInputSet(InputSet):
    """
    An InputSet with methods appropriate for specifying the inputs to the StoreToken
    Choreo. The InputSet object is used to specify input parameters when executing this Choreo.
    """
    def set_Expires(self, value):
        """
        Set the value of the Expires input for this Choreo. ((optional, integer) The lifetime of the token (in seconds). Defaults to 0 indicating no expiration.)
        """
        super(StoreTokenInputSet, self)._set_input('Expires', value)
    def set_Name(self, value):
        """
        Set the value of the Name input for this Choreo. ((required, string) The token name. When a token does not exist, it will be inserted. When a token does exist, an update is performed.)
        """
        super(StoreTokenInputSet, self)._set_input('Name', value)
    def set_Value(self, value):
        """
        Set the value of the Value input for this Choreo. ((required, string) The token value to store. The maximum number of characters for a token is 4096.)
        """
        super(StoreTokenInputSet, self)._set_input('Value', value)

class StoreTokenResultSet(ResultSet):
    """
    A ResultSet with methods tailored to the values returned by the StoreToken Choreo.
    The ResultSet object is used to retrieve the results of a Choreo execution.
    """

    def getJSONFromString(self, str):
        return json.loads(str)

    def get_Updated(self):
        """
        Retrieve the value for the "Updated" output from this Choreo execution. ((boolean) Returns true if token is stored successfully.)
        """
        return self._output.get('Updated', None)

class StoreTokenChoreographyExecution(ChoreographyExecution):

    def _make_result_set(self, response, path):
        return StoreTokenResultSet(response, path)
