# -*- coding: utf-8 -*-

###############################################################################
#
# Haplogroups
# Retrieves maternal and paternal haplogroups for a user's profiles.
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

class Haplogroups(Choreography):

    def __init__(self, temboo_session):
        """
        Create a new instance of the Haplogroups Choreo. A TembooSession object, containing a valid
        set of Temboo credentials, must be supplied.
        """
        super(Haplogroups, self).__init__(temboo_session, '/Library/23andMe/Haplogroups')


    def new_input_set(self):
        return HaplogroupsInputSet()

    def _make_result_set(self, result, path):
        return HaplogroupsResultSet(result, path)

    def _make_execution(self, session, exec_id, path):
        return HaplogroupsChoreographyExecution(session, exec_id, path)

class HaplogroupsInputSet(InputSet):
    """
    An InputSet with methods appropriate for specifying the inputs to the Haplogroups
    Choreo. The InputSet object is used to specify input parameters when executing this Choreo.
    """
    def set_AccessToken(self, value):
        """
        Set the value of the AccessToken input for this Choreo. ((required, string) The Access Token retrieved after completing the OAuth2 process.)
        """
        super(HaplogroupsInputSet, self)._set_input('AccessToken', value)
    def set_TestMode(self, value):
        """
        Set the value of the TestMode input for this Choreo. ((optional, boolean) A boolean flag indicating that the request should be made to the "demo" 23andMe endpoint for testing. Set to 1 for test mode. Defaults to 0.)
        """
        super(HaplogroupsInputSet, self)._set_input('TestMode', value)

class HaplogroupsResultSet(ResultSet):
    """
    A ResultSet with methods tailored to the values returned by the Haplogroups Choreo.
    The ResultSet object is used to retrieve the results of a Choreo execution.
    """

    def getJSONFromString(self, str):
        return json.loads(str)

    def get_Response(self):
        """
        Retrieve the value for the "Response" output from this Choreo execution. ((json) The response from 23AndMe.)
        """
        return self._output.get('Response', None)

class HaplogroupsChoreographyExecution(ChoreographyExecution):

    def _make_result_set(self, response, path):
        return HaplogroupsResultSet(response, path)
