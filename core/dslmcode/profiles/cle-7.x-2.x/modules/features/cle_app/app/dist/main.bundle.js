webpackJsonp([0,4],{

/***/ 1127:
/***/ function(module, exports) {

function webpackEmptyContext(req) {
	throw new Error("Cannot find module '" + req + "'.");
}
webpackEmptyContext.keys = function() { return []; };
webpackEmptyContext.resolve = webpackEmptyContext;
module.exports = webpackEmptyContext;
webpackEmptyContext.id = 1127;


/***/ },

/***/ 1128:
/***/ function(module, exports, __webpack_require__) {

module.exports = __webpack_require__(482);


/***/ },

/***/ 121:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return Assignment; });
var Assignment = (function () {
    function Assignment() {
        this.id = null;
        this.title = null;
        this.type = 'open';
        this.status = true;
        this.created = null;
        this.startDate = null;
        this.endDate = null;
        this.allowLateSubmissions = true;
        this.project = null;
        this.body = null;
        this.critiqueMethod = 'none';
        this.critiquePrivacy = false;
        this.metadata = {};
        this.hierarchy = {};
    }
    return Assignment;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment.js.map

/***/ },

/***/ 122:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "c", function() { return ActionTypes; });
/* harmony export (immutable) */ exports["b"] = createProject;
/* harmony export (immutable) */ exports["d"] = createProjectSuccess;
/* harmony export (immutable) */ exports["h"] = updateProject;
/* harmony export (immutable) */ exports["e"] = updateProjectSuccess;
/* harmony export (immutable) */ exports["g"] = deleteProject;
/* harmony export (immutable) */ exports["a"] = loadProjects;
/* harmony export (immutable) */ exports["f"] = loadProjectsSuccess;
/* unused harmony export loadPermissions */
/* unused harmony export loadPermissionsSuccess */
var ActionTypes = {
    CREATE_PROJECT: 'CREATE_PROJECT',
    CREATE_PROJECT_SUCCESS: 'CREATE_PROJECT_SUCCESS',
    UPDATE_PROJECT: 'UPDATE_PROJECT',
    UPDATE_PROJECT_SUCCESS: 'UPDATE_PROJECT_SUCCESS',
    DELETE_PROJECT: 'DELETE_PROJECT',
    LOAD_PROJECTS: 'LOAD_PROJECTS',
    LOAD_PROJECTS_SUCCESS: 'LOAD_PROJECTS_SUCCESS',
    LOAD_PERMISSIONS: 'LOAD_PERMISSIONS',
    LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS',
    MOVE_PROJECT_ASSIGNMENT: 'MOVE_PROJECT_ASSIGNMENT'
};
function createProject(project) {
    return {
        type: ActionTypes.CREATE_PROJECT,
        payload: project
    };
}
function createProjectSuccess(project) {
    return {
        type: ActionTypes.CREATE_PROJECT_SUCCESS,
        payload: project
    };
}
function updateProject(project) {
    return {
        type: ActionTypes.UPDATE_PROJECT,
        payload: project
    };
}
function updateProjectSuccess(project) {
    return {
        type: ActionTypes.UPDATE_PROJECT_SUCCESS,
        payload: project
    };
}
function deleteProject(project) {
    return {
        type: ActionTypes.DELETE_PROJECT,
        payload: project
    };
}
function loadProjects() {
    return {
        type: ActionTypes.LOAD_PROJECTS,
        payload: {}
    };
}
function loadProjectsSuccess(projects) {
    return {
        type: ActionTypes.LOAD_PROJECTS_SUCCESS,
        payload: projects
    };
}
function loadPermissions() {
    return {
        type: ActionTypes.LOAD_PERMISSIONS,
        payload: {}
    };
}
function loadPermissionsSuccess(permissions) {
    return {
        type: ActionTypes.LOAD_PERMISSIONS_SUCCESS,
        payload: permissions
    };
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project.actions.js.map

/***/ },

/***/ 169:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__elmsln_service__ = __webpack_require__(38);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__app_settings__ = __webpack_require__(95);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__project__ = __webpack_require__(255);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(11);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return ProjectService; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var ProjectService = (function () {
    function ProjectService(elmsln, store) {
        this.elmsln = elmsln;
        this.store = store;
    }
    ProjectService.prototype.getProjects = function () {
        var _this = this;
        return this.elmsln.get(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/projects')
            .map(function (data) { return data.json(); })
            .map(function (data) { return typeof data.data !== 'undefined' ? data.data : []; })
            .map(function (projects) { return projects.map(function (p) { return _this.convertToProject(p); }); });
    };
    ProjectService.prototype.getProject = function (projectId) {
        var _this = this;
        return this.elmsln.get(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/projects/' + projectId)
            .map(function (data) { return data.json().data[0]; })
            .map(function (project) { return _this.convertToProject(project); });
    };
    ProjectService.prototype.createProject = function (project) {
        var _this = this;
        // first we need to prepare the object for Drupal
        return this.elmsln.post(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/projects/create', project)
            .map(function (data) { return data.json().node; })
            .map(function (node) { return _this.convertToProject(node); });
    };
    ProjectService.prototype.updateProject = function (project) {
        var _this = this;
        return this.elmsln.put(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/projects/' + project.id + '/update', project)
            .map(function (data) { return data.json().node; })
            .map(function (node) { return _this.convertToProject(node); });
    };
    ProjectService.prototype.deleteProject = function (project) {
        return this.elmsln.delete(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/projects/' + project.id + '/delete')
            .map(function (data) { return data.json(); });
    };
    ProjectService.prototype.formatProjects = function (projects) {
        var _this = this;
        var newProjects = [];
        projects.forEach(function (project) {
            newProjects.push(_this.convertToProject(project));
        });
        return newProjects;
    };
    ProjectService.prototype.convertToProject = function (data) {
        var converted = new __WEBPACK_IMPORTED_MODULE_3__project__["a" /* Project */]();
        for (var propertyName in converted) {
            if (data[propertyName]) {
                converted[propertyName] = data[propertyName];
            }
        }
        if (data.id) {
            converted.id = Number(data.id);
        }
        if (data.nid) {
            converted.id = Number(data.nid);
        }
        if (data.title) {
            converted.title = data.title;
        }
        // Convert date fields
        var dateFields = ['startDate', 'endDate'];
        dateFields.forEach(function (field) {
            if (converted[field]) {
                converted[field] = new Date(converted[field] * 1000);
            }
        });
        return converted;
    };
    ProjectService.prototype.prepareForDrupal = function (project) {
        var ufProject = {};
        // always specify as cle_project
        ufProject['type'] = "cle_project";
        if (project.title) {
            ufProject['title'] = project.title;
        }
        if (project.author) {
            ufProject['author'] = project.author;
        }
        if (project.description) {
            ufProject['field_project_due_date'] = project.description;
        }
        if (project.startDate) {
            ufProject['field_project_due_date']['value2'] = project.startDate;
        }
        if (project.endDate) {
            ufProject['field_project_due_date']['value'] = project.endDate;
        }
        return ufProject;
    };
    Object.defineProperty(ProjectService.prototype, "userCanEdit", {
        // Return if the user should be able to edit a project
        get: function () {
            return this.store.select('user')
                .map(function (state) { return state.permissions.includes('edit own cle_project content'); });
        },
        enumerable: true,
        configurable: true
    });
    ProjectService = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__elmsln_service__["a" /* ElmslnService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], ProjectService);
    return ProjectService;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project.service.js.map

/***/ },

/***/ 170:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__elmsln_service__ = __webpack_require__(38);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__app_settings__ = __webpack_require__(95);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__submission__ = __webpack_require__(96);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionService; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var SubmissionService = (function () {
    function SubmissionService(elmsln, store) {
        this.elmsln = elmsln;
        this.store = store;
        this.submissions = this.store.select(function (state) { return state.submissions; });
    }
    SubmissionService.prototype.getSubmissions = function (assignmentId) {
        var _this = this;
        var query = assignmentId ? '?assignment=' + assignmentId : '';
        this.elmsln.get(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/submissions' + query)
            .map(function (data) { return data.json(); })
            .map(function (data) { return typeof data.data !== 'undefined' ? data.data : []; })
            .map(function (data) {
            if (data) {
                // convert list of data into list of Submissions
                var d_1 = [];
                data.forEach(function (item) { return d_1.push(_this.convertToSubmission(item)); });
                return d_1;
            }
        })
            .map(function (payload) { return ({ type: 'ADD_SUBMISSIONS', payload: payload }); })
            .subscribe(function (action) { return _this.store.dispatch(action); });
    };
    SubmissionService.prototype.loadSubmissions = function () {
        var _this = this;
        return this.elmsln.get(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/submissions')
            .map(function (data) { return data.json().data; })
            .map(function (data) {
            if (data) {
                // convert list of data into list of Submissions
                var d_2 = [];
                data.forEach(function (item) { return d_2.push(_this.convertToSubmission(item)); });
                return d_2;
            }
        });
    };
    SubmissionService.prototype.getSubmission = function (submissionId) {
        var _this = this;
        return this.elmsln.get(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/submissions/' + submissionId)
            .map(function (data) { return data.json().data[0]; })
            .map(function (data) { return _this.convertToSubmission(data); });
    };
    SubmissionService.prototype.createSubmission = function (submission) {
        var _this = this;
        var newSub = this.prepareForDrupal(submission);
        return this.elmsln.post(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/submissions/create', newSub)
            .map(function (data) { return data.json().node; })
            .map(function (node) { return _this.convertToSubmission(node); });
    };
    SubmissionService.prototype.updateSubmission = function (submission) {
        var _this = this;
        var newSub = this.prepareForDrupal(submission);
        return this.elmsln.put(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/submissions/' + submission.id + '/update', newSub)
            .map(function (data) { return data.json(); })
            .map(function (node) { return _this.convertToSubmission(node); });
    };
    SubmissionService.prototype.deleteSubmission = function (submission) {
        return this.elmsln.delete(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/submissions/' + submission.id + '/delete')
            .map(function (data) { return data.json(); });
    };
    /**
     * @todo: this should eventually be more dynamic
     */
    SubmissionService.prototype.getSubmissionOptions = function () {
        return {
            type: [
                { value: 'open', display: 'Open' },
                { value: 'closed', display: 'Closed' }
            ],
            critiqueMethod: [
                { value: 'open', display: 'Open' },
                { value: 'random', display: 'Random' }
            ],
            critiqueStyle: [
                { value: 'open', display: 'Open' },
                { value: 'blind', display: 'Blind' },
                { value: 'double_blind', display: 'Double blind' }
            ],
            state: [
                { value: 'submission_in_progress', display: 'Submission in progress', icon: 'autorenew', color: 'lightgoldenrodyellow' },
                { value: 'submission_ready', display: 'Submission Ready', icon: 'done', color: 'lightgreen' }
            ]
        };
    };
    SubmissionService.prototype.convertToSubmission = function (data) {
        var converted = new __WEBPACK_IMPORTED_MODULE_4__submission__["a" /* Submission */]();
        for (var propertyName in converted) {
            if (data[propertyName]) {
                converted[propertyName] = data[propertyName];
            }
        }
        if (data['nid']) {
            converted.id = Number(data['nid']);
        }
        if (data.evidence) {
            if (data.evidence.body) {
                converted.body = data.evidence.body;
            }
        }
        return converted;
    };
    SubmissionService.prototype.prepareForDrupal = function (submission) {
        var newSub = Object.assign({}, submission);
        if (submission.body) {
            newSub.evidence = {
                body: {
                    value: submission.body,
                    format: 'textbook_editor'
                }
            };
        }
        if (submission.evidence) {
            if (submission.evidence.images) {
                newSub.evidence['images'] = submission.evidence.images;
            }
        }
        return newSub;
    };
    // get the submission from the store using the submissionID and 
    // return an observable
    SubmissionService.prototype.getSubmissionFromStore = function (submissionId) {
        return this.store.select('submissions')
            .map(function (state) { return state.submissions.find(function (sub) { return sub.id === submissionId; }); });
    };
    // find out if the current user can edit the submission
    SubmissionService.prototype.userCanEditSubmission = function (submissionId) {
        return this.store.select('submissions')
            .map(function (state) { return state.submissions.find(function (sub) { return sub.id === submissionId; }); })
            .map(function (state) {
            if (state) {
                if (typeof state.metadata !== 'undefined') {
                    if (typeof state.metadata.canUpdate !== 'undefined') {
                        return state.metadata.canUpdate;
                    }
                }
            }
            return false;
        });
    };
    SubmissionService = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], SubmissionService);
    return SubmissionService;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.service.js.map

/***/ },

/***/ 171:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__elmsln_service__ = __webpack_require__(38);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ng2_cookies_ng2_cookies__ = __webpack_require__(449);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ng2_cookies_ng2_cookies___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_ng2_cookies_ng2_cookies__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__app_actions__ = __webpack_require__(54);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(11);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return UserService; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var UserService = (function () {
    function UserService(elmslnService, store) {
        this.elmslnService = elmslnService;
        this.store = store;
        this.loggedIn = false;
    }
    UserService.prototype.login = function (username, password) {
        __WEBPACK_IMPORTED_MODULE_2_ng2_cookies_ng2_cookies__["Cookie"].set('basicAuthCredentials', btoa(username + ":" + password));
        this.elmslnService.login();
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__app_actions__["a" /* loadPermissions */])());
    };
    UserService.prototype.logout = function () {
        this.elmslnService.logout();
    };
    UserService.prototype.getCurrentUserId = function () {
        return this.store.select('user')
            .map(function (state) { return state.uid; });
    };
    UserService = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__elmsln_service__["a" /* ElmslnService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], UserService);
    return UserService;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/user.service.js.map

/***/ },

/***/ 253:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__user_service__ = __webpack_require__(171);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__app_actions__ = __webpack_require__(54);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__submission_submission_actions__ = __webpack_require__(80);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__projects_project_actions__ = __webpack_require__(122);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7__app_settings__ = __webpack_require__(95);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AppComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};








var AppComponent = (function () {
    function AppComponent(router, store) {
        this.router = router;
        this.store = store;
    }
    AppComponent.prototype.ngOnInit = function () {
        this.basePath = __WEBPACK_IMPORTED_MODULE_7__app_settings__["a" /* AppSettings */].BASE_PATH;
        // Find out if the user is already logged In
        var auth = localStorage.getItem('basicAuthCredentials');
        if (auth) {
            this.router.navigate(['/projects']);
        }
        else {
            this.router.navigate(['/login']);
        }
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__app_actions__["b" /* loadAssignments */])());
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__app_actions__["a" /* loadPermissions */])());
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__submission_submission_actions__["a" /* loadSubmissions */])());
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__projects_project_actions__["a" /* loadProjects */])());
    };
    AppComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-root',
            template: __webpack_require__(830),
            styles: [__webpack_require__(795)],
            providers: [__WEBPACK_IMPORTED_MODULE_1__user_service__["a" /* UserService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], AppComponent);
    return AppComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.component.js.map

/***/ },

/***/ 254:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_http__ = __webpack_require__(237);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__app_settings__ = __webpack_require__(95);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__elmsln_service__ = __webpack_require__(38);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return CritiqueService; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};




var CritiqueService = (function () {
    function CritiqueService(http, elmslnService) {
        this.http = http;
        this.elmslnService = elmslnService;
    }
    CritiqueService.prototype.getSubmissionCritiques = function (submissionId) {
        return this.elmslnService.get(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'node.json?status=1,type=cle_critique&deep-load-refs=node,user&field_cle_crit_sub_ref=' + submissionId)
            .map(function (data) { return data.json().list; });
    };
    CritiqueService.prototype.createCritique = function (critique) {
        console.log('createCritique');
        var body = {};
        var authorId = '';
        body = {
            type: 'cle_critique',
            title: 'Critique',
            field_cle_crit_feedback: {
                value: critique.body,
                format: 'student_format'
            },
            field_cle_crit_sub_ref: {
                id: critique.submissionId
            },
            author: 4
        };
        return this.elmslnService.post(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'node.json', body);
    };
    /**
     * Instead of doing a hard delete, we are just going to set to
     * unpublish
     */
    CritiqueService.prototype.deleteCritique = function (critique) {
        console.log('unpublish critique');
        var critiqueId = critique.nid;
        var body = {
            "status": "0"
        };
        return this.elmslnService.put(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'node/' + critiqueId + '.json', body);
    };
    CritiqueService = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_http__["b" /* Http */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_http__["b" /* Http */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_3__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__elmsln_service__["a" /* ElmslnService */]) === 'function' && _b) || Object])
    ], CritiqueService);
    return CritiqueService;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/critique.service.js.map

/***/ },

/***/ 255:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return Project; });
var Project = (function () {
    function Project() {
    }
    return Project;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project.js.map

/***/ },

/***/ 256:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(77);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__image_image_actions__ = __webpack_require__(397);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__submission__ = __webpack_require__(96);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionFormComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var SubmissionFormComponent = (function () {
    function SubmissionFormComponent(formBuilder, store) {
        this.formBuilder = formBuilder;
        this.store = store;
        this.onSubmissionSave = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.onSubmissionCancel = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.onFormChanges = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.formValueChanges = 0;
        this.saveAttempted = false;
    }
    SubmissionFormComponent.prototype.ngOnInit = function () {
        var _this = this;
        var form = this.submission;
        this.form = this.formBuilder.group(form);
        this.form.setControl('title', new __WEBPACK_IMPORTED_MODULE_1__angular_forms__["b" /* FormControl */](this.submission.title, __WEBPACK_IMPORTED_MODULE_1__angular_forms__["c" /* Validators */].required));
        this.form.valueChanges
            .subscribe(function () {
            /**
             * @todo: hack to make form dirty work. WYSIWYG is
             * fireing a change event on init
             */
            if (_this.formValueChanges > 1) {
                _this.onFormChanges.emit(_this.form.dirty);
            }
            _this.formValueChanges++;
        });
        this.savingImage$ = this.store.select('images')
            .map(function (s) { return s.status; })
            .map(function (s) { return s.type === 'saving'; });
        /**
         * Saving Image notifications
         */
        var savingImageMessage = "\n      Saving image \n      <div class=\"preloader-wrapper small active\">\n        <div class=\"spinner-layer spinner-green-only\">\n          <div class=\"circle-clipper left\">\n            <div class=\"circle\"></div>\n          </div><div class=\"gap-patch\">\n            <div class=\"circle\"></div>\n          </div><div class=\"circle-clipper right\">\n            <div class=\"circle\"></div>\n          </div>\n        </div>\n      </div>\n    ";
        // when savingImage changes in the reducer
        // change the notifications
        this.store.select('images')
            .map(function (s) { return s.status; })
            .skip(1)
            .debounceTime(200)
            .distinctUntilChanged(function (x, y) { return x === y; })
            .subscribe(function (s) {
            jQuery('.submission-form-image-saving').remove();
            if (s.type === 'saving') {
                Materialize.toast(savingImageMessage, null, 'submission-form-image-saving');
            }
            if (s.type === 'saved') {
                Materialize.toast('Image uploaded', 1500);
            }
            if (s.type === 'error') {
                Materialize.toast(s.message, 1500);
            }
        });
    };
    SubmissionFormComponent.prototype.ngOnChanges = function () {
    };
    SubmissionFormComponent.prototype.onWysiwygInit = function () {
        this.form.markAsPristine();
    };
    SubmissionFormComponent.prototype.onWysiwygImageAdded = function ($event) {
        ;
    };
    SubmissionFormComponent.prototype.onImageSave = function ($event) {
        switch ($event.type) {
            case 'saving':
                this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__image_image_actions__["a" /* createImage */])());
                break;
            case 'success':
                this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__image_image_actions__["b" /* createImageSuccess */])());
                this.addImageAsEvidence($event.image);
                break;
            case 'error':
                this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__image_image_actions__["c" /* createImageFailure */])());
                break;
            default:
                break;
        }
    };
    SubmissionFormComponent.prototype.submit = function () {
        if (this.form.status === 'VALID') {
            this.onSubmissionSave.emit(this.form.value);
        }
        else {
            this.saveAttempted = true;
            if (this.form.get('title').status) {
                alert('The title field is required.');
            }
        }
    };
    SubmissionFormComponent.prototype.cancel = function () {
        this.onSubmissionCancel.emit();
    };
    SubmissionFormComponent.prototype.addImageAsEvidence = function (image) {
        // get the existing images
        var images = typeof this.form.value.evidence.images === 'array' ? this.form.value.evidence.images : [];
        // add this new image fid onto the array
        images.push(image.fid);
        // update the images array in the submission form.
        this.form.patchValue({
            evidence: {
                images: images
            }
        });
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_4__submission__["a" /* Submission */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__submission__["a" /* Submission */]) === 'function' && _a) || Object)
    ], SubmissionFormComponent.prototype, "submission", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _b) || Object)
    ], SubmissionFormComponent.prototype, "onSubmissionSave", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _c) || Object)
    ], SubmissionFormComponent.prototype, "onSubmissionCancel", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _d) || Object)
    ], SubmissionFormComponent.prototype, "onFormChanges", void 0);
    SubmissionFormComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-form',
            template: __webpack_require__(858),
            styles: [__webpack_require__(823)]
        }), 
        __metadata('design:paramtypes', [(typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */]) === 'function' && _e) || Object, (typeof (_f = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */]) === 'function' && _f) || Object])
    ], SubmissionFormComponent);
    return SubmissionFormComponent;
    var _a, _b, _c, _d, _e, _f;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-form.component.js.map

/***/ },

/***/ 38:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_http__ = __webpack_require__(237);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__app_settings__ = __webpack_require__(95);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_ng2_cookies_ng2_cookies__ = __webpack_require__(449);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_ng2_cookies_ng2_cookies___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3_ng2_cookies_ng2_cookies__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(11);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return ElmslnService; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var ElmslnService = (function () {
    function ElmslnService(http, store) {
        this.http = http;
        this.store = store;
    }
    ElmslnService.prototype.createAuthorizationHeader = function (headers) {
        var basicAuthCredentials = __WEBPACK_IMPORTED_MODULE_3_ng2_cookies_ng2_cookies__["Cookie"].get('basicAuthCredentials');
        if (basicAuthCredentials) {
            headers.append('Authorization', 'Basic ' + basicAuthCredentials);
        }
    };
    ElmslnService.prototype.createCSRFTokenHeader = function (headers) {
        this.store.select('user')
            .map(function (state) { return state.token; })
            .subscribe(function (token) {
            headers.append('x-csrf-token', token);
            return headers;
        });
    };
    ElmslnService.prototype.login = function () {
        var headers = new __WEBPACK_IMPORTED_MODULE_1__angular_http__["a" /* Headers */]();
        this.createAuthorizationHeader(headers);
        this.createCSRFTokenHeader(headers);
        return true;
    };
    ElmslnService.prototype.logout = function () {
        __WEBPACK_IMPORTED_MODULE_3_ng2_cookies_ng2_cookies__["Cookie"].delete('basicAuthCredentials');
        // localStorage.clear();
        return true;
    };
    ElmslnService.prototype.get = function (url) {
        var headers = new __WEBPACK_IMPORTED_MODULE_1__angular_http__["a" /* Headers */]();
        this.createAuthorizationHeader(headers);
        // this.createCSRFTokenHeader(headers);
        return this.http.get(url, {
            headers: headers
        });
    };
    ElmslnService.prototype.post = function (url, data) {
        var headers = new __WEBPACK_IMPORTED_MODULE_1__angular_http__["a" /* Headers */]();
        headers.append('Accept', 'application/json');
        headers.append('Content-Type', 'application/json');
        this.createAuthorizationHeader(headers);
        this.createCSRFTokenHeader(headers);
        console.log('Post headers ', headers);
        return this.http.post(url, data, {
            headers: headers
        });
    };
    ElmslnService.prototype.put = function (url, data) {
        var headers = new __WEBPACK_IMPORTED_MODULE_1__angular_http__["a" /* Headers */]();
        this.createAuthorizationHeader(headers);
        this.createCSRFTokenHeader(headers);
        return this.http.put(url, data, {
            headers: headers
        });
    };
    ElmslnService.prototype.delete = function (url) {
        var headers = new __WEBPACK_IMPORTED_MODULE_1__angular_http__["a" /* Headers */]();
        this.createAuthorizationHeader(headers);
        this.createCSRFTokenHeader(headers);
        return this.http.delete(url, {
            headers: headers
        });
    };
    ElmslnService.prototype.getUserProfile = function () {
        return this.get(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/elmsln/user')
            .map(function (data) { return data.json(); });
    };
    /**
     * Create a file entity from base64 image
     */
    ElmslnService.prototype.createImage = function (image) {
        var body = {
            name: 'default-image-name',
            type: 'image',
            /**
             * @todo need to add logic to to specify whether the user uploaded images
             *       file path's are public or private.
             */
            file_wrapper: 'public',
            data: image
        };
        return this.post(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/elmsln/files/create', body)
            .map(function (data) { return data.json().file; });
    };
    // helper to execute callbacks that are located in an objects like nodes and user
    ElmslnService.prototype.evalCallbacks = function (object) {
        try {
            if (object.environment.callbacks) {
                var callbacks = object.environment.callbacks;
                callbacks
                    .map(function (callback) {
                    eval(callback);
                });
            }
        }
        catch (e) { }
    };
    ElmslnService.prototype.exportLifecycleHook = function (componentName) {
        if (typeof Drupal !== 'undefined') {
            Drupal.settings.cleApp = Drupal.settings.cleApp || {};
            Drupal.settings.cleApp.callbacks = Drupal.settings.cleApp.callbacks || {};
            if (typeof Drupal.settings.cleApp.callbacks[componentName] === 'function') {
                var callback = Drupal.settings.cleApp.callbacks[componentName];
                callback();
            }
        }
    };
    ElmslnService = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_http__["b" /* Http */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_http__["b" /* Http */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], ElmslnService);
    return ElmslnService;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/elmsln.service.js.map

/***/ },

/***/ 393:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__assignment__ = __webpack_require__(121);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__assignment_service__ = __webpack_require__(67);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__assignment_form_assignment_form_component__ = __webpack_require__(394);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__app_actions__ = __webpack_require__(54);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AssignmentDialogComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};







var AssignmentDialogComponent = (function () {
    function AssignmentDialogComponent(route, router, assignmentService, el, store) {
        this.route = route;
        this.router = router;
        this.assignmentService = assignmentService;
        this.el = el;
        this.store = store;
        this.assignment = new __WEBPACK_IMPORTED_MODULE_2__assignment__["a" /* Assignment */]();
    }
    AssignmentDialogComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params
            .subscribe(function (params) {
            if (typeof params['assignmentId'] !== 'undefined') {
                _this.action = 'update';
                _this.assignmentService.getAssignment(params['assignmentId'])
                    .subscribe(function (assignment) { return _this.assignment = assignment; });
            }
            else if (typeof params['projectId'] !== 'undefined') {
                var a = new __WEBPACK_IMPORTED_MODULE_2__assignment__["a" /* Assignment */]();
                _this.action = 'create';
                a.project = Number(params['projectId']);
                _this.assignment = a;
            }
            else if (typeof params['deleteAssignmentId'] !== 'undefined') {
                _this.action = 'delete';
                var a = new __WEBPACK_IMPORTED_MODULE_2__assignment__["a" /* Assignment */]();
                a.id = Number(params['deleteAssignmentId']);
                _this.assignment = a;
            }
        });
        jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal({
            dismissible: false,
            ready: function (modal, trigger) {
                /**
                 * @todo: Hack to solve z-index issues when embeded in the Drupal site.
                 */
                jQuery('.modal-overlay').appendTo('app-root');
            },
        });
        jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('open');
    };
    AssignmentDialogComponent.prototype.ngOnDestroy = function () {
        jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('close');
    };
    AssignmentDialogComponent.prototype.onAssignmentSave = function ($event) {
        if ($event.id) {
            this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__app_actions__["d" /* updateAssignment */])($event));
        }
        else {
            this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__app_actions__["e" /* createAssignment */])($event));
        }
        this.router.navigate([{ outlets: { dialog: null } }]);
    };
    AssignmentDialogComponent.prototype.onCancel = function () {
        this.router.navigate([{ outlets: { dialog: null } }]);
    };
    AssignmentDialogComponent.prototype.onSave = function () {
        this.assignmentFormComponent.save();
    };
    AssignmentDialogComponent.prototype.onDelete = function () {
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__app_actions__["f" /* deleteAssignment */])(this.assignment));
        this.router.navigate([{ outlets: { dialog: null } }]);
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["ViewChild"])(__WEBPACK_IMPORTED_MODULE_4__assignment_form_assignment_form_component__["a" /* AssignmentFormComponent */]), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_4__assignment_form_assignment_form_component__["a" /* AssignmentFormComponent */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__assignment_form_assignment_form_component__["a" /* AssignmentFormComponent */]) === 'function' && _a) || Object)
    ], AssignmentDialogComponent.prototype, "assignmentFormComponent", void 0);
    AssignmentDialogComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-assignment-dialog',
            template: __webpack_require__(832),
            styles: [__webpack_require__(797)],
            providers: [__WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _e) || Object, (typeof (_f = typeof __WEBPACK_IMPORTED_MODULE_5__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_5__ngrx_store__["a" /* Store */]) === 'function' && _f) || Object])
    ], AssignmentDialogComponent);
    return AssignmentDialogComponent;
    var _a, _b, _c, _d, _e, _f;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment-dialog.component.js.map

/***/ },

/***/ 394:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(77);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__assignment__ = __webpack_require__(121);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__assignment_service__ = __webpack_require__(67);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AssignmentFormComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var AssignmentFormComponent = (function () {
    function AssignmentFormComponent(formBuilder, assignmentService, router) {
        this.formBuilder = formBuilder;
        this.assignmentService = assignmentService;
        this.router = router;
        // assignment creation event
        this.assignmentSave = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
    }
    AssignmentFormComponent.prototype.ngOnInit = function () {
        // get a list of assignment 'types' that we have available so we can display
        // those in the select field
        this.assignmentOptions = this.assignmentService.getAssignmentOptions();
    };
    AssignmentFormComponent.prototype.ngOnChanges = function () {
        var form = this.assignment;
        // Add validation to the title
        // create the form from the assignment object that we recieved
        this.form = this.formBuilder.group(form);
        this.form.setControl('title', new __WEBPACK_IMPORTED_MODULE_1__angular_forms__["b" /* FormControl */](this.assignment.title, __WEBPACK_IMPORTED_MODULE_1__angular_forms__["c" /* Validators */].required));
        this.assignmentIsCritique = this.assignmentService.assignmentIsCritique(this.assignment);
        /**
         * @todo: first attempt at autoSaveForm
         */
        // this.form.valueChanges
        //   .debounceTime(1000)
        //   .subscribe(() => this.autoSaveForm());
    };
    // private autoSaveForm() {
    //   const saved:Assignment[] = localStorage.getItem('assignments_autosave') ? JSON.parse(localStorage.getItem('assignments_autosave')) : [];
    //   const currentForm:Assignment = this.form.value;
    //   let newSaved:Assignment[];
    //   if (currentForm.id) {
    //     saved.map(assignment => {
    //       if (assignment.id === currentForm.id) {
    //         return currentForm;
    //       }
    //       return assignment;
    //     });
    //   }
    //   else {
    //     newSaved['new_assignment'] = currentForm;
    //   }
    //   localStorage.setItem('assignments_autosave', JSON.stringify(newSaved));
    // }
    AssignmentFormComponent.prototype.save = function () {
        // first check to make sure the form is valid
        if (this.form.status === 'VALID') {
            // emit the assignmentSave and send up the new form
            this.assignmentSave.emit(this.form.value);
            // reset the form 
            this.form.reset();
        }
        else {
            this.saveAttempted = true;
            if (this.form.get('title').status) {
                alert('The title field is required.');
            }
        }
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_3__assignment__["a" /* Assignment */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__assignment__["a" /* Assignment */]) === 'function' && _a) || Object)
    ], AssignmentFormComponent.prototype, "assignment", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _b) || Object)
    ], AssignmentFormComponent.prototype, "assignmentSave", void 0);
    AssignmentFormComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-assignment-form',
            template: __webpack_require__(833),
            styles: [__webpack_require__(798)],
            providers: [__WEBPACK_IMPORTED_MODULE_3__assignment__["a" /* Assignment */], __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */]) === 'function' && _e) || Object])
    ], AssignmentFormComponent);
    return AssignmentFormComponent;
    var _a, _b, _c, _d, _e;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment-form.component.js.map

/***/ },

/***/ 395:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_common__ = __webpack_require__(61);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__assignment_service__ = __webpack_require__(67);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__app_actions__ = __webpack_require__(54);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__elmsln_service__ = __webpack_require__(38);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AssignmentComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};







var AssignmentComponent = (function () {
    function AssignmentComponent(router, route, location, assignmentService, el, store, elmslnService) {
        this.router = router;
        this.route = route;
        this.location = location;
        this.assignmentService = assignmentService;
        this.el = el;
        this.store = store;
        this.elmslnService = elmslnService;
    }
    AssignmentComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params.forEach(function (params) {
            if (params['id']) {
                var id = +params['id'];
                _this.assignmentId = Number(id);
            }
        });
        // check the permissions store to see if the user has edit
        this.userCanEdit$ = this.store.select('user')
            .map(function (state) {
            if (state.permissions.includes('edit any cle_assignment content')) {
                return true;
            }
            return false;
        });
        // get my submissions
        this.submissions$ = this.store.select('submissions')
            .map(function (state) { return state.submissions.filter(function (sub) { return sub.assignment === _this.assignmentId; }); });
        /**
         * @example: this is an example of how we could use another Observable to filter submissions
         */
        // this.submissions$ = Observable.zip(
        //   this.store.select('submissions').map((state:any) => state.submissions.filter(sub => sub.assignment === this.assignmentId)),
        //   this.store.select('user').map((state:any) => state.uid),
        //   (submissions, uid) => {
        //     // make sure that the submission author has my uid
        //     return submissions.filter(sub => sub.uid === uid);
        //   }
        // )
        if (this.assignmentId) {
            this.assignments$ = this.store.select('assignments')
                .map(function (state) { return state.assignments.find(function (assignment) {
                return assignment.id === _this.assignmentId;
            }); })
                .map(function (state) {
                return [state];
            });
        }
    };
    AssignmentComponent.prototype.ngAfterViewChecked = function () {
    };
    AssignmentComponent.prototype.onEditAssignment = function (assignment) {
        var url = 'assignment-edit/' + assignment.id;
        this.router.navigate([{ outlets: { dialog: url } }]);
    };
    AssignmentComponent.prototype.onCreateSubmission = function (assignment) {
        var url = 'submissions/create/' + assignment.id;
        this.router.navigate([url]);
    };
    AssignmentComponent.prototype.onStartCritique = function (assignment) {
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__app_actions__["c" /* startCritque */])(assignment));
    };
    AssignmentComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'cle-assignment',
            template: __webpack_require__(835),
            styles: [__webpack_require__(800)],
            providers: [__WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _e) || Object, (typeof (_f = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _f) || Object, (typeof (_g = typeof __WEBPACK_IMPORTED_MODULE_6__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_6__elmsln_service__["a" /* ElmslnService */]) === 'function' && _g) || Object])
    ], AssignmentComponent);
    return AssignmentComponent;
    var _a, _b, _c, _d, _e, _f, _g;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment.component.js.map

/***/ },

/***/ 396:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return DialogComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

var DialogComponent = (function () {
    function DialogComponent(el) {
        this.el = el;
        this.action = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
    }
    DialogComponent.prototype.ngOnInit = function () {
        jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal({
            dismissible: false,
            ready: function (modal, trigger) {
                /**
                 * @todo: Hack to solve z-index issues when embeded in the Drupal site.
                 */
                jQuery('.modal-overlay').appendTo('app-root');
            },
        });
    };
    DialogComponent.prototype.ngOnDestroy = function () {
        this.close();
    };
    DialogComponent.prototype.open = function () {
        jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('open');
    };
    DialogComponent.prototype.close = function () {
        jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('close');
    };
    DialogComponent.prototype.onSave = function () {
        this.action.emit('save');
    };
    DialogComponent.prototype.onCancel = function () {
        this.action.emit('cancel');
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', Object)
    ], DialogComponent.prototype, "content", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', Object)
    ], DialogComponent.prototype, "footer", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _a) || Object)
    ], DialogComponent.prototype, "action", void 0);
    DialogComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-dialog',
            template: __webpack_require__(842),
            styles: [__webpack_require__(807)]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _b) || Object])
    ], DialogComponent);
    return DialogComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/dialog.component.js.map

/***/ },

/***/ 397:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "d", function() { return ActionTypes; });
/* harmony export (immutable) */ exports["a"] = createImage;
/* harmony export (immutable) */ exports["b"] = createImageSuccess;
/* harmony export (immutable) */ exports["c"] = createImageFailure;
var ActionTypes = {
    CREATE_IMAGE: 'CREATE_IMAGE',
    CREATE_IMAGE_SUCCESS: 'CREATE_IMAGE_SUCCESS',
    CREATE_IMAGE_FAILURE: 'CREATE_IMAGE_FAILURE'
};
function createImage() {
    return {
        type: ActionTypes.CREATE_IMAGE,
        payload: {}
    };
}
function createImageSuccess() {
    return {
        type: ActionTypes.CREATE_IMAGE_SUCCESS,
        payload: {}
    };
}
function createImageFailure() {
    return {
        type: ActionTypes.CREATE_IMAGE_FAILURE,
        payload: {}
    };
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/image.actions.js.map

/***/ },

/***/ 398:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(77);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__user_service__ = __webpack_require__(171);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(11);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return LoginComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var LoginComponent = (function () {
    function LoginComponent(fb, userService, router, store) {
        this.fb = fb;
        this.userService = userService;
        this.router = router;
        this.store = store;
        this.form = this.fb.group({
            username: '',
            password: ''
        });
    }
    LoginComponent.prototype.ngOnInit = function () {
        // check if we are being loaded within a Drupal site, if we are, skip
        // the basic auth login
        if (typeof Drupal !== 'undefined') {
            console.log('Drupal detected...');
            this.userService.logout();
            this.router.navigate(['/projects']);
        }
    };
    LoginComponent.prototype.submitForm = function () {
        // save new critique
        if (this.form.value.username && this.form.value.password) {
            var loggedIn = this.userService.login(this.form.value.username, this.form.value.password);
            this.router.navigate(['/projects']);
        }
    };
    LoginComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-login',
            template: __webpack_require__(846),
            styles: [__webpack_require__(811)],
            providers: [__WEBPACK_IMPORTED_MODULE_2__user_service__["a" /* UserService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__user_service__["a" /* UserService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__user_service__["a" /* UserService */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_3__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _d) || Object])
    ], LoginComponent);
    return LoginComponent;
    var _a, _b, _c, _d;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/login.component.js.map

/***/ },

/***/ 399:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__user_service__ = __webpack_require__(171);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_router__ = __webpack_require__(16);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return LogoutComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};



var LogoutComponent = (function () {
    function LogoutComponent(userService, router) {
        this.userService = userService;
        this.router = router;
    }
    LogoutComponent.prototype.ngOnInit = function () {
        // Log the user out
        this.userService.logout();
        // redirect to the homepage
        this.router.navigate(['/']);
    };
    LogoutComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-logout',
            template: __webpack_require__(847),
            styles: [__webpack_require__(812)],
            providers: [__WEBPACK_IMPORTED_MODULE_1__user_service__["a" /* UserService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__user_service__["a" /* UserService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__user_service__["a" /* UserService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */]) === 'function' && _b) || Object])
    ], LogoutComponent);
    return LogoutComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/logout.component.js.map

/***/ },

/***/ 400:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__project__ = __webpack_require__(255);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__project_service__ = __webpack_require__(169);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__project_actions__ = __webpack_require__(122);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return ProjectsListComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};






var ProjectsListComponent = (function () {
    function ProjectsListComponent(projectService, router, store) {
        this.projectService = projectService;
        this.router = router;
        this.store = store;
        this.projects = [];
        this.userCanEdit$ = this.projectService.userCanEdit;
    }
    ProjectsListComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.projects$ = this.store.select('projects')
            .map(function (state) { return state.projects; });
        this.store.select('projects')
            .map(function (state) { return state.projects; })
            .subscribe(function (projects) { return _this.projectCount = projects.length; });
    };
    ProjectsListComponent.prototype.createNewProject = function (title) {
        var newProj = new __WEBPACK_IMPORTED_MODULE_1__project__["a" /* Project */]();
        newProj.title = "New Project";
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__project_actions__["b" /* createProject */])(newProj));
    };
    ProjectsListComponent.prototype.projectDeleted = function (deletedProject) {
        var _this = this;
        this.projects.forEach(function (project, index) {
            if (project.id == deletedProject.id) {
                _this.projects.splice(index, 1);
            }
        });
    };
    ProjectsListComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-projects-list',
            template: __webpack_require__(850),
            styles: [__webpack_require__(815)],
            providers: [__WEBPACK_IMPORTED_MODULE_2__project_service__["a" /* ProjectService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__project_service__["a" /* ProjectService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__project_service__["a" /* ProjectService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_3__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__angular_router__["a" /* Router */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _c) || Object])
    ], ProjectsListComponent);
    return ProjectsListComponent;
    var _a, _b, _c;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/projects-list.component.js.map

/***/ },

/***/ 401:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__submission__ = __webpack_require__(96);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__submission_actions__ = __webpack_require__(80);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__submission_form_submission_form_component__ = __webpack_require__(256);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionCreateComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};






var SubmissionCreateComponent = (function () {
    function SubmissionCreateComponent(route, router, store) {
        this.route = route;
        this.router = router;
        this.store = store;
        this.isSaving = false;
    }
    SubmissionCreateComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params
            .subscribe(function (params) {
            if (typeof params['assignmentId'] !== 'undefined') {
                var id = params['assignmentId'];
                _this.assignmentId = Number(id);
                _this.submission = Object.assign({}, new __WEBPACK_IMPORTED_MODULE_3__submission__["a" /* Submission */](), { assignment: _this.assignmentId });
            }
        });
        // check the permissions store to see if the user has edit
        this.userCanEdit$ = this.store.select('user')
            .map(function (state) { return state.permissions.includes('edit own cle_submission content'); });
        this.store.select('submissions')
            .map(function (state) { return state.saving; })
            .subscribe(function (saving) {
            // saving is happening
            if (saving && !_this.isSaving) {
                _this.isSaving = true;
                Materialize.toast('Creating submission...', 30000, 'toast-submission-create');
            }
            else if (!saving && _this.isSaving) {
                jQuery('.toast-submission-create').remove();
                Materialize.toast('Submission created', 1500);
                _this.router.navigate(['/assignments/' + _this.assignmentId]);
            }
        });
    };
    SubmissionCreateComponent.prototype.onSubmissionSave = function ($event) {
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__submission_actions__["b" /* createSubmission */])($event));
    };
    SubmissionCreateComponent.prototype.onSubmissionCancel = function ($event) {
        this.router.navigate(['/assignments/' + this.assignmentId]);
        this.submissionFormComponent.form.reset();
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["ViewChild"])(__WEBPACK_IMPORTED_MODULE_5__submission_form_submission_form_component__["a" /* SubmissionFormComponent */]), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_5__submission_form_submission_form_component__["a" /* SubmissionFormComponent */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_5__submission_form_submission_form_component__["a" /* SubmissionFormComponent */]) === 'function' && _a) || Object)
    ], SubmissionCreateComponent.prototype, "submissionFormComponent", void 0);
    SubmissionCreateComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-create',
            template: __webpack_require__(852),
            styles: [__webpack_require__(817)]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */]) === 'function' && _d) || Object])
    ], SubmissionCreateComponent);
    return SubmissionCreateComponent;
    var _a, _b, _c, _d;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-create.component.js.map

/***/ },

/***/ 402:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__submission_service__ = __webpack_require__(170);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionDialogComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};



var SubmissionDialogComponent = (function () {
    function SubmissionDialogComponent(el, router, route, submissionService) {
        this.el = el;
        this.router = router;
        this.route = route;
        this.submissionService = submissionService;
    }
    SubmissionDialogComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params
            .map(function (params) {
            if (typeof params['submissionId']) {
                _this.submission$ = _this.submissionService.getSubmissionFromStore(params['submissionId']);
            }
        });
        jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal({
            dismissible: false,
            ready: function (modal, trigger) {
                /**
                 * @todo: Hack to solve z-index issues when embeded in the Drupal site.
                 */
                jQuery('.modal-overlay').appendTo('app-root');
            },
        });
        jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('open');
    };
    SubmissionDialogComponent.prototype.ngOnDestroy = function () {
        jQuery(this.el.nativeElement.getElementsByClassName('modal')).modal('close');
    };
    SubmissionDialogComponent.prototype.onCancel = function () {
        this.router.navigate([{ outlets: { dialog: null } }]);
    };
    SubmissionDialogComponent.prototype.onSave = function () {
    };
    SubmissionDialogComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-dialog',
            template: __webpack_require__(855),
            styles: [__webpack_require__(820)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_2__submission_service__["a" /* SubmissionService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__submission_service__["a" /* SubmissionService */]) === 'function' && _d) || Object])
    ], SubmissionDialogComponent);
    return SubmissionDialogComponent;
    var _a, _b, _c, _d;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-dialog.component.js.map

/***/ },

/***/ 403:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__submission_actions__ = __webpack_require__(80);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__submission_form_submission_form_component__ = __webpack_require__(256);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionEditComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var SubmissionEditComponent = (function () {
    function SubmissionEditComponent(route, router, store, el) {
        this.route = route;
        this.router = router;
        this.store = store;
        this.el = el;
        this.isSaving = false;
        this.isCritique = false;
    }
    SubmissionEditComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params.forEach(function (params) {
            if (typeof params['submissionId'] !== 'undefined') {
                var id = params['submissionId'];
                _this.submissionId = Number(id);
            }
        });
        if (this.submissionId) {
            this.submission$ = this.store.select('submissions')
                .map(function (state) { return state.submissions.find(function (sub) {
                _this.assignmentId = sub.assignment;
                return sub.id === _this.submissionId;
            }); });
        }
        this.store.select('submissions')
            .map(function (state) { return state.saving; })
            .subscribe(function (saving) {
            // saving is happening
            if (saving && !_this.isSaving) {
                _this.isSaving = true;
                Materialize.toast('Updating submission...', 30000, 'toast-submission-update');
            }
            else if (!saving && _this.isSaving) {
                jQuery('.toast-submission-update').remove();
                Materialize.toast('Submission updated', 1500);
                _this.router.navigate(['/assignments/' + _this.assignmentId]);
            }
        });
        // get the current assignemnt
        this.assignment$ = this.submission$
            .filter(function (s) {
            if (s) {
                if (s.assignment) {
                    return true;
                }
            }
            return false;
        })
            .mergeMap(function (s) {
            return _this.store.select('assignments')
                .map(function (state) { return state.assignments.find(function (a) { return a.id === s.assignment; }); });
        });
        this.assignment$
            .subscribe(function (assignment) {
            if (assignment.critiqueMethod !== 'none') {
                _this.isCritique = true;
            }
        });
    };
    SubmissionEditComponent.prototype.onSubmissionSave = function ($event) {
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["c" /* updateSubmission */])($event));
        // this.submissionFormComponent.form.reset();
    };
    SubmissionEditComponent.prototype.onSubmissionCancel = function () {
        if (this.submissionFormDirty) {
            if (confirm('You have unsaved changes. Are you sure you want to navigate away from this page?')) {
                this.router.navigate(['/submissions/' + this.submissionId]);
            }
        }
        else {
            this.router.navigate(['/submissions/' + this.submissionId]);
            this.submissionFormComponent.form.reset();
        }
    };
    SubmissionEditComponent.prototype.onFormChanges = function ($event) {
        this.submissionFormDirty = $event;
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["ViewChild"])(__WEBPACK_IMPORTED_MODULE_4__submission_form_submission_form_component__["a" /* SubmissionFormComponent */]), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_4__submission_form_submission_form_component__["a" /* SubmissionFormComponent */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__submission_form_submission_form_component__["a" /* SubmissionFormComponent */]) === 'function' && _a) || Object)
    ], SubmissionEditComponent.prototype, "submissionFormComponent", void 0);
    SubmissionEditComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-edit',
            template: __webpack_require__(857),
            styles: [__webpack_require__(822)]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _e) || Object])
    ], SubmissionEditComponent);
    return SubmissionEditComponent;
    var _a, _b, _c, _d, _e;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-edit.component.js.map

/***/ },

/***/ 404:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__submission__ = __webpack_require__(96);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__submission_service__ = __webpack_require__(170);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__submission_actions__ = __webpack_require__(80);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__dialog_dialog_component__ = __webpack_require__(396);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionStatesComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};







var SubmissionStatesComponent = (function () {
    function SubmissionStatesComponent(submissionService, router, store) {
        this.submissionService = submissionService;
        this.router = router;
        this.store = store;
        this.dialogContent = "\n    Are you sure you want to change the state of this submission?\n  ";
    }
    SubmissionStatesComponent.prototype.ngOnInit = function () {
        this.originalSubmission = this.submission;
    };
    SubmissionStatesComponent.prototype.ngOnChanges = function () {
        var _this = this;
        // get the list of states this submission could be
        var options = this.submissionService.getSubmissionOptions();
        options.state
            .map(function (state) {
            // check if this state is the active state of the submission
            // add an active property to the active state
            state['active'] = state.value === _this.submission.state;
            // add custom inline styles if the item is active
            var styles = {};
            if (state.active) {
                styles = {
                    'color': state.color,
                    'background': state.color
                };
            }
            state['styles'] = styles;
            return state;
        });
        this.states = options.state;
        // everytime the submission changes, look and see if the submission state
        // was updated
        if (typeof this.originalSubmission !== 'undefined') {
            if (this.originalSubmission.state !== this.submission.state) {
                Materialize.toast('Submission state updated', 1500);
            }
        }
        this.originalSubmission = this.submission;
    };
    SubmissionStatesComponent.prototype.onStateClick = function (item) {
        if (typeof this.submission.metadata.canUpdate !== 'undefined') {
            if (this.submission.metadata.canUpdate) {
                this.selectedState = item.value;
                this.dialogComponent.open();
            }
        }
    };
    SubmissionStatesComponent.prototype.onDialogAction = function ($event) {
        if ($event === 'cancel') {
            this.dialogComponent.close();
        }
        if ($event === 'save') {
            var newSub = Object.assign({}, this.submission, { state: this.selectedState });
            this.dialogComponent.close();
            this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__submission_actions__["c" /* updateSubmission */])(newSub));
        }
        // reset the selected state
        this.selectedState = '';
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_3__submission__["a" /* Submission */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__submission__["a" /* Submission */]) === 'function' && _a) || Object)
    ], SubmissionStatesComponent.prototype, "submission", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["ViewChild"])(__WEBPACK_IMPORTED_MODULE_6__dialog_dialog_component__["a" /* DialogComponent */]), 
        __metadata('design:type', (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_6__dialog_dialog_component__["a" /* DialogComponent */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_6__dialog_dialog_component__["a" /* DialogComponent */]) === 'function' && _b) || Object)
    ], SubmissionStatesComponent.prototype, "dialogComponent", void 0);
    SubmissionStatesComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-states',
            template: __webpack_require__(860),
            styles: [__webpack_require__(794)]
        }), 
        __metadata('design:paramtypes', [(typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_4__submission_service__["a" /* SubmissionService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__submission_service__["a" /* SubmissionService */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */]) === 'function' && _e) || Object])
    ], SubmissionStatesComponent);
    return SubmissionStatesComponent;
    var _a, _b, _c, _d, _e;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-states.component.js.map

/***/ },

/***/ 405:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_common__ = __webpack_require__(61);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__elmsln_service__ = __webpack_require__(38);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var SubmissionComponent = (function () {
    function SubmissionComponent(route, store, router, location, elmslnService) {
        this.route = route;
        this.store = store;
        this.router = router;
        this.location = location;
        this.elmslnService = elmslnService;
    }
    SubmissionComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params
            .subscribe(function (params) {
            if (params['submissionId']) {
                _this.submissionId = Number(params['submissionId']);
                // get the submission
                _this.submission$ = _this.store.select('submissions')
                    .map(function (state) { return state.submissions.find(function (sub) {
                    if (sub.id === _this.submissionId) {
                        _this.assignmentId = sub.assignment;
                        return true;
                    }
                    else {
                        return false;
                    }
                }); });
                // check if the user can edit the submission
                _this.userCanEdit$ = _this.submission$
                    .map(function (state) {
                    if (state) {
                        if (typeof state.metadata !== 'undefined') {
                            if (typeof state.metadata.canUpdate !== 'undefined') {
                                return state.metadata.canUpdate;
                            }
                        }
                    }
                    return false;
                });
            }
        });
    };
    SubmissionComponent.prototype.onClickBack = function () {
        this.router.navigate(['/assignments/' + this.assignmentId]);
    };
    SubmissionComponent.prototype.editSubmission = function () {
        this.router.navigate(['/submissions/' + this.submissionId + '/edit']);
    };
    SubmissionComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission',
            template: __webpack_require__(861),
            styles: [__webpack_require__(825)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_4__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__elmsln_service__["a" /* ElmslnService */]) === 'function' && _e) || Object])
    ], SubmissionComponent);
    return SubmissionComponent;
    var _a, _b, _c, _d, _e;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.component.js.map

/***/ },

/***/ 481:
/***/ function(module, exports) {

function webpackEmptyContext(req) {
	throw new Error("Cannot find module '" + req + "'.");
}
webpackEmptyContext.keys = function() { return []; };
webpackEmptyContext.resolve = webpackEmptyContext;
module.exports = webpackEmptyContext;
webpackEmptyContext.id = 481;


/***/ },

/***/ 482:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__polyfills_ts__ = __webpack_require__(636);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__polyfills_ts___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0__polyfills_ts__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_platform_browser_dynamic__ = __webpack_require__(562);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__environments_environment__ = __webpack_require__(635);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__app___ = __webpack_require__(619);





if (__WEBPACK_IMPORTED_MODULE_3__environments_environment__["a" /* environment */].production) {
    __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__angular_core__["enableProdMode"])();
}
__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1__angular_platform_browser_dynamic__["a" /* platformBrowserDynamic */])().bootstrapModule(__WEBPACK_IMPORTED_MODULE_4__app___["a" /* AppModule */]);
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/main.js.map

/***/ },

/***/ 54:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__assignment__ = __webpack_require__(121);
/* harmony export (binding) */ __webpack_require__.d(exports, "g", function() { return ActionTypes; });
/* harmony export (immutable) */ exports["e"] = createAssignment;
/* harmony export (immutable) */ exports["h"] = createAssignmentSuccess;
/* harmony export (immutable) */ exports["o"] = createCritiqueAssignment;
/* harmony export (immutable) */ exports["i"] = createCritiqueAssignmentSuccess;
/* harmony export (immutable) */ exports["d"] = updateAssignment;
/* harmony export (immutable) */ exports["j"] = updateAssignmentSuccess;
/* harmony export (immutable) */ exports["f"] = deleteAssignment;
/* harmony export (immutable) */ exports["b"] = loadAssignments;
/* harmony export (immutable) */ exports["k"] = loadAssignmentsSuccess;
/* harmony export (immutable) */ exports["a"] = loadPermissions;
/* harmony export (immutable) */ exports["l"] = loadPermissionsSuccess;
/* harmony export (immutable) */ exports["c"] = startCritque;
/* harmony export (immutable) */ exports["m"] = startCritqueSuccess;
/* harmony export (immutable) */ exports["n"] = startCritqueFailure;

var ActionTypes = {
    CREATE_ASSIGNMENT: 'CREATE_ASSIGNMENT',
    CREATE_ASSIGNMENT_SUCCESS: 'CREATE_ASSIGNMENT_SUCCESS',
    CREATE_CRITIQUE_ASSIGNMENT: 'CREATE_CRITIQUE_ASSIGNMENT',
    CREATE_CRITIQUE_ASSIGNMENT_SUCCESS: 'CREATE_CRITIQUE_ASSIGNMENT_SUCCESS',
    UPDATE_ASSIGNMENT: 'UPDATE_ASSIGNMENT',
    UPDATE_ASSIGNMENT_SUCCESS: 'UPDATE_ASSIGNMENT_SUCCESS',
    DELETE_ASSIGNMENT: 'DELETE_ASSIGNMENT',
    LOAD_ASSIGNMENTS: 'LOAD_ASSIGNMENTS',
    LOAD_ASSIGNMENTS_SUCCESS: 'LOAD_ASSIGNMENTS_SUCCESS',
    LOAD_PERMISSIONS: 'LOAD_PERMISSIONS',
    LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS',
    START_CRITQUE: 'START_CRITQUE',
    START_CRITQUE_SUCCESS: 'START_CRITQUE_SUCCESS',
    START_CRITQUE_FAILURE: 'START_CRITQUE_FAILURE',
};
function createAssignment(assignment) {
    return {
        type: ActionTypes.CREATE_ASSIGNMENT,
        payload: assignment
    };
}
function createAssignmentSuccess(assignmentId) {
    return {
        type: ActionTypes.CREATE_ASSIGNMENT_SUCCESS,
        payload: { id: assignmentId }
    };
}
function createCritiqueAssignment(assignment) {
    var newAssignment = Object.assign(new __WEBPACK_IMPORTED_MODULE_0__assignment__["a" /* Assignment */], {
        title: assignment.title + ' critique',
        hierarchy: {
            dependencies: [assignment.id],
            project: assignment.project
        },
        critiqueMethod: 'random',
        startDate: assignment.startDate,
        endDate: assignment.endDate
    });
    return {
        type: ActionTypes.CREATE_CRITIQUE_ASSIGNMENT,
        payload: newAssignment
    };
}
function createCritiqueAssignmentSuccess(assignment) {
    return {
        type: ActionTypes.CREATE_CRITIQUE_ASSIGNMENT_SUCCESS,
        payload: assignment
    };
}
function updateAssignment(assignment) {
    return {
        type: ActionTypes.UPDATE_ASSIGNMENT,
        payload: assignment
    };
}
function updateAssignmentSuccess(assignment) {
    return {
        type: ActionTypes.UPDATE_ASSIGNMENT_SUCCESS,
        payload: assignment
    };
}
function deleteAssignment(assignment) {
    return {
        type: ActionTypes.DELETE_ASSIGNMENT,
        payload: assignment
    };
}
function loadAssignments() {
    return {
        type: ActionTypes.LOAD_ASSIGNMENTS,
        payload: {}
    };
}
function loadAssignmentsSuccess(assignments) {
    return {
        type: ActionTypes.LOAD_ASSIGNMENTS_SUCCESS,
        payload: assignments
    };
}
function loadPermissions() {
    return {
        type: ActionTypes.LOAD_PERMISSIONS,
        payload: {}
    };
}
function loadPermissionsSuccess(permissions, token, uid) {
    return {
        type: ActionTypes.LOAD_PERMISSIONS_SUCCESS,
        payload: { permissions: permissions, token: token, uid: uid }
    };
}
function startCritque(assignment) {
    return {
        type: ActionTypes.START_CRITQUE,
        payload: assignment
    };
}
function startCritqueSuccess(assignment) {
    return {
        type: ActionTypes.START_CRITQUE_SUCCESS,
        payload: assignment
    };
}
function startCritqueFailure(res) {
    return {
        type: ActionTypes.START_CRITQUE_FAILURE,
        payload: res
    };
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.actions.js.map

/***/ },

/***/ 603:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__ = __webpack_require__(182);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_rxjs_add_operator_catch__ = __webpack_require__(451);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_rxjs_add_operator_catch___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_rxjs_add_operator_catch__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_rxjs_Observable__ = __webpack_require__(0);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_rxjs_Observable___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3_rxjs_Observable__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_effects__ = __webpack_require__(168);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__app_actions__ = __webpack_require__(54);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__submission_submission_actions__ = __webpack_require__(80);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7__assignment_service__ = __webpack_require__(67);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8__elmsln_service__ = __webpack_require__(38);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AppEffects; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};









var AppEffects = (function () {
    function AppEffects(actions$, assignmentService, elmslnService) {
        var _this = this;
        this.actions$ = actions$;
        this.assignmentService = assignmentService;
        this.elmslnService = elmslnService;
        this.createAssignment$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_5__app_actions__["g" /* ActionTypes */].CREATE_ASSIGNMENT)
            .mergeMap(function (action) { return _this.assignmentService.createAssignment(action.payload); })
            .map(function (assignmentId) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__app_actions__["h" /* createAssignmentSuccess */])(assignmentId); });
        this.createCritiqueAssignment$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_5__app_actions__["g" /* ActionTypes */].CREATE_CRITIQUE_ASSIGNMENT)
            .mergeMap(function (action) {
            return _this.assignmentService.createAssignment(action.payload)
                .mergeMap(function (assignmentId) { return _this.assignmentService.getAssignment(assignmentId); });
        })
            .map(function (assignment) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__app_actions__["i" /* createCritiqueAssignmentSuccess */])(assignment); });
        // Update the assignment on the server
        this.updateAssignment$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_5__app_actions__["g" /* ActionTypes */].UPDATE_ASSIGNMENT)
            .mergeMap(function (action) {
            return _this.assignmentService.updateAssignment(action.payload)
                .mergeMap(function (data) { return _this.assignmentService.getAssignment(action.payload.id); });
        })
            .map(function (assignment) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__app_actions__["j" /* updateAssignmentSuccess */])(assignment); });
        this.loadAssignments$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_5__app_actions__["g" /* ActionTypes */].LOAD_ASSIGNMENTS)
            .mergeMap(function () { return _this.assignmentService.loadAssignments(); })
            .map(function (assignments) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__app_actions__["k" /* loadAssignmentsSuccess */])(assignments); });
        // Populate the user.permissions store when the user profile returns
        this.loadPermissions$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_5__app_actions__["g" /* ActionTypes */].LOAD_PERMISSIONS)
            .mergeMap(function () { return _this.elmslnService.getUserProfile(); })
            .map(function (profile) {
            if (typeof profile.user.permissions !== 'undefined') {
                return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__app_actions__["l" /* loadPermissionsSuccess */])(profile.user.permissions, profile.user['csrf-token'], Number(profile.user['uid']));
            }
            else {
                return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__app_actions__["l" /* loadPermissionsSuccess */])([], null, null);
            }
        });
        this.deleteAssignment$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_5__app_actions__["g" /* ActionTypes */].DELETE_ASSIGNMENT)
            .mergeMap(function (action) { return _this.assignmentService.deleteAssignment(action.payload); })
            .map(function (info) {
            Materialize.toast('Assignment deleted', 1000);
        });
        this.startCritique$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_5__app_actions__["g" /* ActionTypes */].START_CRITQUE)
            .switchMap(function (action) { return _this.assignmentService.startCritique(action.payload)
            .map(function (res) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__app_actions__["m" /* startCritqueSuccess */])(res.node); })
            .catch(function (res) { return __WEBPACK_IMPORTED_MODULE_3_rxjs_Observable__["Observable"].of(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_5__app_actions__["n" /* startCritqueFailure */])(res)); }); });
        this.startCritqueSuccess$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_5__app_actions__["g" /* ActionTypes */].START_CRITQUE_SUCCESS)
            .map(function (action) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__submission_submission_actions__["a" /* loadSubmissions */])(); });
        this.startCritiqueFailure$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_5__app_actions__["g" /* ActionTypes */].START_CRITQUE_FAILURE)
            .map(function (state) { return state.payload; })
            .map(function (res) {
            // get the reason from the Response & convert to json
            var text = JSON.parse(res.text());
            var reason = text.detail ? text.detail : '';
            Materialize.toast('Could not start critique. ' + reason, 2500);
        });
    }
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "createAssignment$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "createCritiqueAssignment$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "updateAssignment$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "loadAssignments$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "loadPermissions$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["a" /* Effect */])({ dispatch: false }), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "deleteAssignment$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "startCritique$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "startCritqueSuccess$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["a" /* Effect */])({ dispatch: false }), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "startCritiqueFailure$", void 0);
    AppEffects = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["b" /* Actions */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_effects__["b" /* Actions */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_7__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_7__assignment_service__["a" /* AssignmentService */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_8__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_8__elmsln_service__["a" /* ElmslnService */]) === 'function' && _c) || Object])
    ], AppEffects);
    return AppEffects;
    var _a, _b, _c;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.effects.js.map

/***/ },

/***/ 604:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_platform_browser__ = __webpack_require__(165);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_forms__ = __webpack_require__(77);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__angular_http__ = __webpack_require__(237);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__app_routing__ = __webpack_require__(605);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__ngrx_store_devtools__ = __webpack_require__(599);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7__ngrx_effects__ = __webpack_require__(168);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8__ngrx_router_store__ = __webpack_require__(595);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9__reducers_assignments__ = __webpack_require__(625);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10__reducers_users__ = __webpack_require__(626);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11__submission_submission_reducer__ = __webpack_require__(632);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12__projects_project_reducer__ = __webpack_require__(623);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_13__image_image_reducer__ = __webpack_require__(618);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_14__app_effects__ = __webpack_require__(603);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_15__submission_submission_effects__ = __webpack_require__(631);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_16__projects_project_effects__ = __webpack_require__(622);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_17__elmsln_service__ = __webpack_require__(38);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_18__critique_service__ = __webpack_require__(254);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_19__assignment_service__ = __webpack_require__(67);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_20__submission_submission_service__ = __webpack_require__(170);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_21__project_service__ = __webpack_require__(169);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_22_angular2_moment__ = __webpack_require__(637);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_22_angular2_moment___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_22_angular2_moment__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_23__app_component__ = __webpack_require__(253);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_24__assignment_assignment_component__ = __webpack_require__(395);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_25__assignment_assignment_list_assignment_list_component__ = __webpack_require__(607);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_26__dashboard_dashboard_component__ = __webpack_require__(613);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_27__user_user_component__ = __webpack_require__(633);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_28__critique_critique_component__ = __webpack_require__(612);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_29__critique_critique_form_critique_form_component__ = __webpack_require__(610);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_30__login_login_component__ = __webpack_require__(398);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_31__logout_logout_component__ = __webpack_require__(399);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_32__critique_critique_list_critique_list_component__ = __webpack_require__(611);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_33__wysiwygjs_wysiwygjs_component__ = __webpack_require__(634);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_34__assignment_assignment_form_assignment_form_component__ = __webpack_require__(394);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_35__projects_projects_component__ = __webpack_require__(624);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_36__projects_projects_list_projects_list_component__ = __webpack_require__(400);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_37__components_dropdown_dropdown_component__ = __webpack_require__(608);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_38__projects_project_card_project_card_component__ = __webpack_require__(620);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_39__projects_project_item_project_item_component__ = __webpack_require__(621);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_40__editable_field_editable_field_component__ = __webpack_require__(615);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_41__datetime_input_datetime_input_component__ = __webpack_require__(614);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_42__assignment_assignment_dialog_assignment_dialog_component__ = __webpack_require__(393);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_43__submission_submission_create_submission_create_component__ = __webpack_require__(401);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_44__submission_submission_form_submission_form_component__ = __webpack_require__(256);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_45__submission_submission_list_submission_list_component__ = __webpack_require__(630);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_46__submission_submission_detail_submission_detail_component__ = __webpack_require__(628);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_47__submission_submission_component__ = __webpack_require__(405);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_48__submission_submission_edit_submission_edit_component__ = __webpack_require__(403);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_49__submission_submission_states_submission_states_component__ = __webpack_require__(404);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_50__dialog_dialog_component__ = __webpack_require__(396);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_51__submission_submission_edit_states_submission_edit_states_component__ = __webpack_require__(629);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_52__submission_submission_dialog_submission_dialog_component__ = __webpack_require__(402);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_53__image_image_component__ = __webpack_require__(617);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_54__assignment_assignment_detail_assignment_detail_component__ = __webpack_require__(606);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_55__elmsln_wysiwyg_elmsln_wysiwyg_component__ = __webpack_require__(616);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_56__submission_submission_critique_form_submission_critique_form_component__ = __webpack_require__(627);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AppModule; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

























































var AppModule = (function () {
    function AppModule() {
    }
    AppModule = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1__angular_core__["NgModule"])({
            declarations: [
                __WEBPACK_IMPORTED_MODULE_23__app_component__["a" /* AppComponent */],
                __WEBPACK_IMPORTED_MODULE_24__assignment_assignment_component__["a" /* AssignmentComponent */],
                __WEBPACK_IMPORTED_MODULE_25__assignment_assignment_list_assignment_list_component__["a" /* AssignmentListComponent */],
                __WEBPACK_IMPORTED_MODULE_26__dashboard_dashboard_component__["a" /* DashboardComponent */],
                __WEBPACK_IMPORTED_MODULE_27__user_user_component__["a" /* UserComponent */],
                __WEBPACK_IMPORTED_MODULE_28__critique_critique_component__["a" /* CritiqueComponent */],
                __WEBPACK_IMPORTED_MODULE_29__critique_critique_form_critique_form_component__["a" /* CritiqueFormComponent */],
                __WEBPACK_IMPORTED_MODULE_30__login_login_component__["a" /* LoginComponent */],
                __WEBPACK_IMPORTED_MODULE_31__logout_logout_component__["a" /* LogoutComponent */],
                __WEBPACK_IMPORTED_MODULE_32__critique_critique_list_critique_list_component__["a" /* CritiqueListComponent */],
                __WEBPACK_IMPORTED_MODULE_33__wysiwygjs_wysiwygjs_component__["a" /* WysiwygjsComponent */],
                __WEBPACK_IMPORTED_MODULE_34__assignment_assignment_form_assignment_form_component__["a" /* AssignmentFormComponent */],
                __WEBPACK_IMPORTED_MODULE_35__projects_projects_component__["a" /* ProjectsComponent */],
                __WEBPACK_IMPORTED_MODULE_36__projects_projects_list_projects_list_component__["a" /* ProjectsListComponent */],
                __WEBPACK_IMPORTED_MODULE_37__components_dropdown_dropdown_component__["a" /* DropdownComponent */],
                __WEBPACK_IMPORTED_MODULE_38__projects_project_card_project_card_component__["a" /* ProjectCardComponent */],
                __WEBPACK_IMPORTED_MODULE_39__projects_project_item_project_item_component__["a" /* ProjectItemComponent */],
                __WEBPACK_IMPORTED_MODULE_40__editable_field_editable_field_component__["a" /* EditableFieldComponent */],
                __WEBPACK_IMPORTED_MODULE_41__datetime_input_datetime_input_component__["a" /* DatetimeInputComponent */],
                __WEBPACK_IMPORTED_MODULE_42__assignment_assignment_dialog_assignment_dialog_component__["a" /* AssignmentDialogComponent */],
                __WEBPACK_IMPORTED_MODULE_47__submission_submission_component__["a" /* SubmissionComponent */],
                __WEBPACK_IMPORTED_MODULE_43__submission_submission_create_submission_create_component__["a" /* SubmissionCreateComponent */],
                __WEBPACK_IMPORTED_MODULE_44__submission_submission_form_submission_form_component__["a" /* SubmissionFormComponent */],
                __WEBPACK_IMPORTED_MODULE_45__submission_submission_list_submission_list_component__["a" /* SubmissionListComponent */],
                __WEBPACK_IMPORTED_MODULE_46__submission_submission_detail_submission_detail_component__["a" /* SubmissionDetailComponent */],
                __WEBPACK_IMPORTED_MODULE_48__submission_submission_edit_submission_edit_component__["a" /* SubmissionEditComponent */],
                __WEBPACK_IMPORTED_MODULE_49__submission_submission_states_submission_states_component__["a" /* SubmissionStatesComponent */],
                __WEBPACK_IMPORTED_MODULE_50__dialog_dialog_component__["a" /* DialogComponent */],
                __WEBPACK_IMPORTED_MODULE_51__submission_submission_edit_states_submission_edit_states_component__["a" /* SubmissionEditStatesComponent */],
                __WEBPACK_IMPORTED_MODULE_52__submission_submission_dialog_submission_dialog_component__["a" /* SubmissionDialogComponent */],
                __WEBPACK_IMPORTED_MODULE_53__image_image_component__["a" /* ImageComponent */],
                __WEBPACK_IMPORTED_MODULE_54__assignment_assignment_detail_assignment_detail_component__["a" /* AssignmentDetailComponent */],
                __WEBPACK_IMPORTED_MODULE_54__assignment_assignment_detail_assignment_detail_component__["a" /* AssignmentDetailComponent */],
                __WEBPACK_IMPORTED_MODULE_55__elmsln_wysiwyg_elmsln_wysiwyg_component__["a" /* ElmslnWysiwygComponent */],
                __WEBPACK_IMPORTED_MODULE_56__submission_submission_critique_form_submission_critique_form_component__["a" /* SubmissionCritiqueFormComponent */]
            ],
            imports: [
                __WEBPACK_IMPORTED_MODULE_0__angular_platform_browser__["b" /* BrowserModule */],
                __WEBPACK_IMPORTED_MODULE_3__angular_http__["c" /* HttpModule */],
                __WEBPACK_IMPORTED_MODULE_4__app_routing__["a" /* routing */],
                __WEBPACK_IMPORTED_MODULE_2__angular_forms__["e" /* FormsModule */],
                __WEBPACK_IMPORTED_MODULE_2__angular_forms__["f" /* ReactiveFormsModule */],
                __WEBPACK_IMPORTED_MODULE_22_angular2_moment__["MomentModule"],
                __WEBPACK_IMPORTED_MODULE_5__ngrx_store__["g" /* StoreModule */].provideStore({
                    router: __WEBPACK_IMPORTED_MODULE_8__ngrx_router_store__["a" /* routerReducer */],
                    assignments: __WEBPACK_IMPORTED_MODULE_9__reducers_assignments__["a" /* reducer */],
                    user: __WEBPACK_IMPORTED_MODULE_10__reducers_users__["a" /* reducer */],
                    submissions: __WEBPACK_IMPORTED_MODULE_11__submission_submission_reducer__["a" /* submissionReducer */],
                    projects: __WEBPACK_IMPORTED_MODULE_12__projects_project_reducer__["a" /* projectReducer */],
                    images: __WEBPACK_IMPORTED_MODULE_13__image_image_reducer__["a" /* imageReducer */]
                }),
                __WEBPACK_IMPORTED_MODULE_8__ngrx_router_store__["b" /* RouterStoreModule */].connectRouter(),
                __WEBPACK_IMPORTED_MODULE_7__ngrx_effects__["c" /* EffectsModule */].run(__WEBPACK_IMPORTED_MODULE_14__app_effects__["a" /* AppEffects */]),
                __WEBPACK_IMPORTED_MODULE_7__ngrx_effects__["c" /* EffectsModule */].run(__WEBPACK_IMPORTED_MODULE_15__submission_submission_effects__["a" /* SubmissionEffects */]),
                __WEBPACK_IMPORTED_MODULE_7__ngrx_effects__["c" /* EffectsModule */].run(__WEBPACK_IMPORTED_MODULE_16__projects_project_effects__["a" /* ProjectEffects */]),
                __WEBPACK_IMPORTED_MODULE_6__ngrx_store_devtools__["a" /* StoreDevtoolsModule */].instrumentOnlyWithExtension()
            ],
            providers: [
                __WEBPACK_IMPORTED_MODULE_17__elmsln_service__["a" /* ElmslnService */],
                __WEBPACK_IMPORTED_MODULE_18__critique_service__["a" /* CritiqueService */],
                __WEBPACK_IMPORTED_MODULE_19__assignment_service__["a" /* AssignmentService */],
                __WEBPACK_IMPORTED_MODULE_20__submission_submission_service__["a" /* SubmissionService */],
                __WEBPACK_IMPORTED_MODULE_21__project_service__["a" /* ProjectService */]
            ],
            bootstrap: [__WEBPACK_IMPORTED_MODULE_23__app_component__["a" /* AppComponent */]]
        }), 
        __metadata('design:paramtypes', [])
    ], AppModule);
    return AppModule;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.module.js.map

/***/ },

/***/ 605:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__app_component__ = __webpack_require__(253);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__assignment_assignment_component__ = __webpack_require__(395);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__login_login_component__ = __webpack_require__(398);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__logout_logout_component__ = __webpack_require__(399);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__projects_projects_list_projects_list_component__ = __webpack_require__(400);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__assignment_assignment_dialog_assignment_dialog_component__ = __webpack_require__(393);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7__submission_submission_component__ = __webpack_require__(405);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8__submission_submission_create_submission_create_component__ = __webpack_require__(401);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9__submission_submission_edit_submission_edit_component__ = __webpack_require__(403);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10__submission_submission_dialog_submission_dialog_component__ = __webpack_require__(402);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11__submission_submission_states_submission_states_component__ = __webpack_require__(404);
/* unused harmony export appRoutingProviders */
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return routing; });












var appRoutes = [
    {
        path: '',
        component: __WEBPACK_IMPORTED_MODULE_1__app_component__["a" /* AppComponent */]
    },
    {
        path: 'login',
        component: __WEBPACK_IMPORTED_MODULE_3__login_login_component__["a" /* LoginComponent */]
    },
    {
        path: 'logout',
        component: __WEBPACK_IMPORTED_MODULE_4__logout_logout_component__["a" /* LogoutComponent */]
    },
    {
        path: 'projects',
        component: __WEBPACK_IMPORTED_MODULE_5__projects_projects_list_projects_list_component__["a" /* ProjectsListComponent */]
    },
    {
        path: 'assignments/:id',
        component: __WEBPACK_IMPORTED_MODULE_2__assignment_assignment_component__["a" /* AssignmentComponent */],
    },
    {
        path: 'assignment-create/:projectId',
        outlet: 'dialog',
        component: __WEBPACK_IMPORTED_MODULE_6__assignment_assignment_dialog_assignment_dialog_component__["a" /* AssignmentDialogComponent */]
    },
    {
        path: 'assignment-edit/:assignmentId',
        outlet: 'dialog',
        component: __WEBPACK_IMPORTED_MODULE_6__assignment_assignment_dialog_assignment_dialog_component__["a" /* AssignmentDialogComponent */]
    },
    {
        path: 'assignment-delete/:deleteAssignmentId',
        outlet: 'dialog',
        component: __WEBPACK_IMPORTED_MODULE_6__assignment_assignment_dialog_assignment_dialog_component__["a" /* AssignmentDialogComponent */]
    },
    {
        path: 'submissions',
        children: [
            {
                path: 'create/:assignmentId',
                component: __WEBPACK_IMPORTED_MODULE_8__submission_submission_create_submission_create_component__["a" /* SubmissionCreateComponent */]
            },
            {
                path: ':submissionId',
                component: __WEBPACK_IMPORTED_MODULE_7__submission_submission_component__["a" /* SubmissionComponent */]
            },
            {
                path: ':submissionId/edit',
                component: __WEBPACK_IMPORTED_MODULE_9__submission_submission_edit_submission_edit_component__["a" /* SubmissionEditComponent */]
            },
            {
                path: 'submission-states',
                component: __WEBPACK_IMPORTED_MODULE_11__submission_submission_states_submission_states_component__["a" /* SubmissionStatesComponent */]
            }
        ]
    },
    {
        path: 'submissions/:submissionId/edit-state',
        outlet: 'dialog',
        component: __WEBPACK_IMPORTED_MODULE_10__submission_submission_dialog_submission_dialog_component__["a" /* SubmissionDialogComponent */]
    }
];
var appRoutingProviders = [];
var routing = __WEBPACK_IMPORTED_MODULE_0__angular_router__["c" /* RouterModule */].forRoot(appRoutes);
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.routing.js.map

/***/ },

/***/ 606:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__assignment__ = __webpack_require__(121);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AssignmentDetailComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};


var AssignmentDetailComponent = (function () {
    function AssignmentDetailComponent() {
    }
    AssignmentDetailComponent.prototype.ngOnInit = function () {
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__assignment__["a" /* Assignment */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__assignment__["a" /* Assignment */]) === 'function' && _a) || Object)
    ], AssignmentDetailComponent.prototype, "assignment", void 0);
    AssignmentDetailComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-assignment-detail',
            template: __webpack_require__(831),
            styles: [__webpack_require__(796)]
        }), 
        __metadata('design:paramtypes', [])
    ], AssignmentDetailComponent);
    return AssignmentDetailComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment-detail.component.js.map

/***/ },

/***/ 607:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__assignment_service__ = __webpack_require__(67);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__app_actions__ = __webpack_require__(54);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AssignmentListComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var AssignmentListComponent = (function () {
    function AssignmentListComponent(assignmentService, router, store) {
        this.assignmentService = assignmentService;
        this.router = router;
        this.store = store;
        this.userCanEdit$ = this.assignmentService.userCanEdit;
    }
    AssignmentListComponent.prototype.ngOnInit = function () {
    };
    AssignmentListComponent.prototype.viewAssignment = function (assignmentId) {
        if (assignmentId) {
            this.router.navigate(['/assignments/' + assignmentId]);
        }
    };
    AssignmentListComponent.prototype.createAssignment = function () {
        this.router.navigate(['/assignments/new']);
    };
    AssignmentListComponent.prototype.onEditAssignment = function (assignment) {
        var url = 'assignment-edit/' + assignment.id;
        this.router.navigate([{ outlets: { dialog: url } }]);
    };
    AssignmentListComponent.prototype.onDeleteAssignment = function (assignment) {
        var url = 'assignment-delete/' + assignment.id;
        this.router.navigate([{ outlets: { dialog: url } }]);
    };
    AssignmentListComponent.prototype.addCritique = function (assignment) {
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__app_actions__["o" /* createCritiqueAssignment */])(assignment));
    };
    // when we get new assignments, make sure we sort them
    AssignmentListComponent.prototype.ngOnChanges = function () {
        this.sortAssignmentsByDate();
    };
    AssignmentListComponent.prototype.sortAssignmentsByDate = function () {
        if (this.assignments) {
            this.assignments.sort(function (a, b) {
                var aDate = null;
                var bDate = null;
                if (!a.startDate) {
                    aDate = a.endDate;
                }
                if (!b.startDate) {
                    bDate = b.endDate;
                }
                if (aDate && bDate) {
                    if (aDate < bDate) {
                        return -1;
                    }
                    else if (aDate > bDate) {
                        return 1;
                    }
                    else {
                        return 0;
                    }
                }
                else if (aDate && !bDate) {
                    return -1;
                }
                else if (!aDate && bDate) {
                    return 1;
                }
            });
        }
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', Array)
    ], AssignmentListComponent.prototype, "assignments", void 0);
    AssignmentListComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'cle-assignment-list',
            template: __webpack_require__(834),
            styles: [__webpack_require__(799)],
            providers: [__WEBPACK_IMPORTED_MODULE_1__assignment_service__["a" /* AssignmentService */]],
            changeDetection: __WEBPACK_IMPORTED_MODULE_0__angular_core__["ChangeDetectionStrategy"].OnPush
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__assignment_service__["a" /* AssignmentService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */]) === 'function' && _c) || Object])
    ], AssignmentListComponent);
    return AssignmentListComponent;
    var _a, _b, _c;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment-list.component.js.map

/***/ },

/***/ 608:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return DropdownComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

var DropdownComponent = (function () {
    function DropdownComponent(el) {
        this.el = el;
    }
    DropdownComponent.prototype.ngOnInit = function () {
        $(this.el.nativeElement.firstElementChild).dropdown();
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])('button'), 
        __metadata('design:type', String)
    ], DropdownComponent.prototype, "button", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])('links'), 
        __metadata('design:type', Array)
    ], DropdownComponent.prototype, "links", void 0);
    DropdownComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-dropdown',
            template: __webpack_require__(836),
            styles: [__webpack_require__(801)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _a) || Object])
    ], DropdownComponent);
    return DropdownComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/dropdown.component.js.map

/***/ },

/***/ 609:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return Critique; });
var Critique = (function () {
    function Critique(body) {
        this.body = body;
    }
    return Critique;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/critique.js.map

/***/ },

/***/ 610:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__critique__ = __webpack_require__(609);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__critique_service__ = __webpack_require__(254);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_rxjs_Rx__ = __webpack_require__(866);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_rxjs_Rx___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3_rxjs_Rx__);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return CritiqueFormComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};




var CritiqueFormComponent = (function () {
    function CritiqueFormComponent(critiqueService) {
        this.critiqueService = critiqueService;
        this.showPreview = false;
        this.initialContent = '';
        this.update$ = new __WEBPACK_IMPORTED_MODULE_3_rxjs_Rx__["Subject"]();
        this.critiqueCreated = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
    }
    CritiqueFormComponent.prototype.ngOnInit = function () {
    };
    CritiqueFormComponent.prototype.submitForm = function () {
        var _this = this;
        if (this.content) {
            var newCritique = new __WEBPACK_IMPORTED_MODULE_1__critique__["a" /* Critique */](this.content);
            newCritique.submissionId = this.submission.nid;
            this.critiqueService.createCritique(newCritique)
                .subscribe(function (res) {
                if (res.ok) {
                    _this.content = '';
                    _this.critiqueCreated.emit(res.json());
                }
            });
        }
        else {
        }
    };
    CritiqueFormComponent.prototype.onFocus = function () {
    };
    // When the content changes in the wysiwyg update the content variable
    CritiqueFormComponent.prototype.onChange = function ($event) {
        this.content = $event;
        console.log(this.content);
    };
    CritiqueFormComponent.prototype.onBlur = function () {
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', Object)
    ], CritiqueFormComponent.prototype, "submission", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _a) || Object)
    ], CritiqueFormComponent.prototype, "critiqueCreated", void 0);
    CritiqueFormComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'cle-critique-form',
            template: __webpack_require__(837),
            styles: [__webpack_require__(802)],
            providers: [__WEBPACK_IMPORTED_MODULE_2__critique_service__["a" /* CritiqueService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__critique_service__["a" /* CritiqueService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__critique_service__["a" /* CritiqueService */]) === 'function' && _b) || Object])
    ], CritiqueFormComponent);
    return CritiqueFormComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/critique-form.component.js.map

/***/ },

/***/ 611:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__critique_service__ = __webpack_require__(254);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return CritiqueListComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};


var CritiqueListComponent = (function () {
    function CritiqueListComponent(critiqueService) {
        this.critiqueService = critiqueService;
    }
    CritiqueListComponent.prototype.ngOnInit = function () {
        this.getCritiques();
    };
    CritiqueListComponent.prototype.getCritiques = function () {
        var _this = this;
        this.critiqueService.getSubmissionCritiques(this.submission.nid)
            .subscribe(function (data) {
            _this.critiques = data;
        });
    };
    CritiqueListComponent.prototype.deleteCritique = function (critique) {
        var _this = this;
        this.critiqueService.deleteCritique(critique)
            .subscribe(function (data) {
            console.log(data);
            _this.getCritiques();
        });
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', Object)
    ], CritiqueListComponent.prototype, "submission", void 0);
    CritiqueListComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'cle-critique-list',
            template: __webpack_require__(838),
            styles: [__webpack_require__(803)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__critique_service__["a" /* CritiqueService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__critique_service__["a" /* CritiqueService */]) === 'function' && _a) || Object])
    ], CritiqueListComponent);
    return CritiqueListComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/critique-list.component.js.map

/***/ },

/***/ 612:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_common__ = __webpack_require__(61);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return CritiqueComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};



var CritiqueComponent = (function () {
    function CritiqueComponent(route, location) {
        this.route = route;
        this.location = location;
    }
    CritiqueComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params.forEach(function (params) {
            var id = +params['id'];
            _this.submissionId = id;
        });
    };
    CritiqueComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'cle-critique',
            template: __webpack_require__(839),
            styles: [__webpack_require__(804)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */]) === 'function' && _b) || Object])
    ], CritiqueComponent);
    return CritiqueComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/critique.component.js.map

/***/ },

/***/ 613:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__assignment_service__ = __webpack_require__(67);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return DashboardComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};


var DashboardComponent = (function () {
    function DashboardComponent(assignmentService) {
        this.assignmentService = assignmentService;
    }
    DashboardComponent.prototype.ngOnInit = function () {
    };
    DashboardComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'cle-dashboard',
            template: __webpack_require__(840),
            styles: [__webpack_require__(805)],
            providers: [__WEBPACK_IMPORTED_MODULE_1__assignment_service__["a" /* AssignmentService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__assignment_service__["a" /* AssignmentService */]) === 'function' && _a) || Object])
    ], DashboardComponent);
    return DashboardComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/dashboard.component.js.map

/***/ },

/***/ 614:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(77);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return DatetimeInputComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};


var DatetimeInputComponent = (function () {
    function DatetimeInputComponent() {
        this.propagateChange = function (_) { };
    }
    // this series of functions enable the ControlValueAccessor to work.
    // see http://blog.thoughtram.io/angular/2016/07/27/custom-form-controls-in-angular-2.html
    DatetimeInputComponent.prototype.writeValue = function (value) {
        if (value) {
            // if we do have a date set then we need to split out the day and the time
            var d = new Date(value);
            // convert it to an ISO string
            var dString = d.toISOString();
            // split the string at the time(T)
            var dSplit = dString.split("T");
            // split the string starting at the seconds(.)
            var tSplit = dSplit[1].split('.');
            // set the day and time values
            this.day = dSplit[0];
            this.time = tSplit[0];
        }
        else {
            // if there isn't a date value we are going
            this.day = '';
            this.time = '';
        }
        // Update the @Input
        this.date = value;
    };
    DatetimeInputComponent.prototype.registerOnChange = function (fn) {
        this.propagateChange = fn;
    };
    DatetimeInputComponent.prototype.registerOnTouched = function () {
    };
    // convert day and time into a date and uptdate the date property
    DatetimeInputComponent.prototype.updateDatetime = function () {
        if (typeof this.day !== 'undefined') {
            var d = void 0;
            d = this.day;
            // if there is a time then add that to the string
            if (typeof this.time !== 'undefined') {
                d = d + ' ' + this.time;
            }
            // convert string into date
            var date = new Date(d);
            this.date = date;
            this.propagateChange(this.date);
        }
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', Object)
    ], DatetimeInputComponent.prototype, "date", void 0);
    DatetimeInputComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-datetime-input',
            template: __webpack_require__(841),
            styles: [__webpack_require__(806)],
            providers: [
                {
                    provide: __WEBPACK_IMPORTED_MODULE_1__angular_forms__["d" /* NG_VALUE_ACCESSOR */],
                    useExisting: __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["forwardRef"])(function () { return DatetimeInputComponent; }),
                    multi: true
                }]
        }), 
        __metadata('design:paramtypes', [])
    ], DatetimeInputComponent);
    return DatetimeInputComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/datetime-input.component.js.map

/***/ },

/***/ 615:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(77);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return EditableFieldComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};


var EditableFieldComponent = (function () {
    function EditableFieldComponent(el, formBuilder) {
        this.el = el;
        this.formBuilder = formBuilder;
        this.type = 'text';
        this.content = '';
        this.contentUpdated = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.editing = false;
        this.form = this.formBuilder.group({
            content: this.content
        });
    }
    EditableFieldComponent.prototype.ngOnInit = function () {
        this.form.patchValue({
            content: this.content
        });
    };
    EditableFieldComponent.prototype.beginEditing = function () {
        this.editing = true;
    };
    EditableFieldComponent.prototype.endEditing = function () {
        var _this = this;
        this.editing = false;
        setTimeout(function () { return _this.saveNewContent(); }, 400);
    };
    EditableFieldComponent.prototype.saveNewContent = function () {
        this.contentUpdated.emit(this.form.value.content);
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', String)
    ], EditableFieldComponent.prototype, "type", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', String)
    ], EditableFieldComponent.prototype, "content", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _a) || Object)
    ], EditableFieldComponent.prototype, "contentUpdated", void 0);
    EditableFieldComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-editable-field',
            template: __webpack_require__(843),
            styles: [__webpack_require__(808)]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */]) === 'function' && _c) || Object])
    ], EditableFieldComponent);
    return EditableFieldComponent;
    var _a, _b, _c;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/editable-field.component.js.map

/***/ },

/***/ 616:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return ElmslnWysiwygComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

var ElmslnWysiwygComponent = (function () {
    function ElmslnWysiwygComponent() {
    }
    ElmslnWysiwygComponent.prototype.ngOnInit = function () {
    };
    ElmslnWysiwygComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-elmsln-wysiwyg',
            template: __webpack_require__(844),
            styles: [__webpack_require__(809)]
        }), 
        __metadata('design:paramtypes', [])
    ], ElmslnWysiwygComponent);
    return ElmslnWysiwygComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/elmsln-wysiwyg.component.js.map

/***/ },

/***/ 617:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return ImageComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

var ImageComponent = (function () {
    function ImageComponent() {
    }
    ImageComponent.prototype.ngOnInit = function () {
    };
    ImageComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-image',
            template: __webpack_require__(845),
            styles: [__webpack_require__(810)]
        }), 
        __metadata('design:paramtypes', [])
    ], ImageComponent);
    return ImageComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/image.component.js.map

/***/ },

/***/ 618:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__image_actions__ = __webpack_require__(397);
/* harmony export (immutable) */ exports["a"] = imageReducer;

var initialState = {
    status: {
        type: 'default',
        message: ''
    }
};
function imageReducer(state, action) {
    if (state === void 0) { state = initialState; }
    switch (action.type) {
        case __WEBPACK_IMPORTED_MODULE_0__image_actions__["d" /* ActionTypes */].CREATE_IMAGE: {
            return {
                status: {
                    type: 'saving',
                    message: ''
                }
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__image_actions__["d" /* ActionTypes */].CREATE_IMAGE_SUCCESS: {
            return {
                status: {
                    type: 'saved',
                    message: 'Image created'
                }
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__image_actions__["d" /* ActionTypes */].CREATE_IMAGE_FAILURE: {
            return {
                status: {
                    type: 'error',
                    message: 'There was an error creating the image.'
                }
            };
        }
        default: {
            return state;
        }
    }
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/image.reducer.js.map

/***/ },

/***/ 619:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__app_component__ = __webpack_require__(253);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__app_module__ = __webpack_require__(604);
/* unused harmony namespace reexport */
/* harmony namespace reexport (by used) */ __webpack_require__.d(exports, "a", function() { return __WEBPACK_IMPORTED_MODULE_1__app_module__["a"]; });


//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/index.js.map

/***/ },

/***/ 620:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return ProjectCardComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

var ProjectCardComponent = (function () {
    function ProjectCardComponent() {
    }
    ProjectCardComponent.prototype.ngOnInit = function () {
    };
    ProjectCardComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-project-card',
            template: __webpack_require__(848),
            styles: [__webpack_require__(813)]
        }), 
        __metadata('design:paramtypes', [])
    ], ProjectCardComponent);
    return ProjectCardComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project-card.component.js.map

/***/ },

/***/ 621:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__project__ = __webpack_require__(255);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__project_service__ = __webpack_require__(169);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__assignment_service__ = __webpack_require__(67);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__project_actions__ = __webpack_require__(122);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return ProjectItemComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};







var ProjectItemComponent = (function () {
    function ProjectItemComponent(projectService, assignmentService, el, router, store) {
        var _this = this;
        this.projectService = projectService;
        this.assignmentService = assignmentService;
        this.el = el;
        this.router = router;
        this.store = store;
        this.delete = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.userCanEdit$ = this.projectService.userCanEdit;
        this.assignments = store.select('assignments')
            .map(function (state) { return state.assignments.filter(function (assignment) { return assignment.project === _this.project.id; }); });
    }
    ProjectItemComponent.prototype.ngOnInit = function () {
        jQuery(this.el.nativeElement.getElementsByClassName('delete-project-form')).modal({
            ready: function (modal, trigger) {
                /**
                 * @todo: Hack to solve z-index issues when embeded in the Drupal site.
                 */
                jQuery('.modal-overlay').appendTo('app-root');
            },
        });
        jQuery(this.el.nativeElement.getElementsByClassName('tooltipped')).tooltip({ delay: 40 });
    };
    ProjectItemComponent.prototype.ngOnDestroy = function () {
        jQuery(this.el.nativeElement.getElementsByClassName('tooltipped')).tooltip('remove');
    };
    ProjectItemComponent.prototype.onCreateAssignment = function () {
        var url = 'assignment-create/' + this.project.id;
        this.router.navigate([{ outlets: { dialog: url } }]);
    };
    ProjectItemComponent.prototype.onDeleteProject = function () {
        jQuery(this.el.nativeElement.getElementsByClassName('delete-project-form')).modal('open');
    };
    ProjectItemComponent.prototype.confirmDelete = function (confirm) {
        if (confirm) {
            var project = this.project;
            this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__project_actions__["g" /* deleteProject */])(project));
        }
        else {
            jQuery(this.el.nativeElement.getElementsByClassName('delete-project-form')).modal('close');
        }
    };
    ProjectItemComponent.prototype.updateTitle = function ($event) {
        // remember the old title in case the update fails
        var oldTitle = this.project.title;
        // update the project title on the page
        if (oldTitle !== $event) {
            this.project.title = $event;
            // the project object that we are going to save
            var newProject = {
                id: this.project.id,
                title: this.project.title
            };
            this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__project_actions__["h" /* updateProject */])(newProject));
        }
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__project__["a" /* Project */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__project__["a" /* Project */]) === 'function' && _a) || Object)
    ], ProjectItemComponent.prototype, "project", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _b) || Object)
    ], ProjectItemComponent.prototype, "delete", void 0);
    ProjectItemComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-project-item',
            template: __webpack_require__(849),
            styles: [__webpack_require__(814)],
            providers: [__WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */]],
            changeDetection: __WEBPACK_IMPORTED_MODULE_0__angular_core__["ChangeDetectionStrategy"].OnPush
        }), 
        __metadata('design:paramtypes', [(typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_3__project_service__["a" /* ProjectService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__project_service__["a" /* ProjectService */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _e) || Object, (typeof (_f = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _f) || Object, (typeof (_g = typeof __WEBPACK_IMPORTED_MODULE_5__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_5__ngrx_store__["a" /* Store */]) === 'function' && _g) || Object])
    ], ProjectItemComponent);
    return ProjectItemComponent;
    var _a, _b, _c, _d, _e, _f, _g;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project-item.component.js.map

/***/ },

/***/ 622:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__ = __webpack_require__(182);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__ = __webpack_require__(168);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__project_actions__ = __webpack_require__(122);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__project_service__ = __webpack_require__(169);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return ProjectEffects; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var ProjectEffects = (function () {
    function ProjectEffects(actions$, projectService) {
        var _this = this;
        this.actions$ = actions$;
        this.projectService = projectService;
        this.createProject$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__project_actions__["c" /* ActionTypes */].CREATE_PROJECT)
            .mergeMap(function (action) { return _this.projectService.createProject(action.payload); })
            .mergeMap(function (project) { return _this.projectService.getProject(project.id); })
            .map(function (project) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__project_actions__["d" /* createProjectSuccess */])(project); });
        // Update the project on the server
        this.updateProject$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__project_actions__["c" /* ActionTypes */].UPDATE_PROJECT)
            .mergeMap(function (action) {
            return _this.projectService.updateProject(action.payload)
                .mergeMap(function (data) { return _this.projectService.getProject(action.payload.id); });
        })
            .map(function (project) {
            Materialize.toast('Project updated', 1500);
            return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__project_actions__["e" /* updateProjectSuccess */])(project);
        });
        this.loadProjects$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__project_actions__["c" /* ActionTypes */].LOAD_PROJECTS)
            .mergeMap(function () { return _this.projectService.getProjects(); })
            .map(function (projects) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__project_actions__["f" /* loadProjectsSuccess */])(projects); });
        this.deleteProject$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__project_actions__["c" /* ActionTypes */].DELETE_PROJECT)
            .mergeMap(function (action) { return _this.projectService.deleteProject(action.payload); })
            .map(function (info) {
            if (info.status === '200') {
                Materialize.toast('Project deleted', 1000);
            }
        });
    }
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], ProjectEffects.prototype, "createProject$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], ProjectEffects.prototype, "updateProject$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], ProjectEffects.prototype, "loadProjects$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])({ dispatch: false }), 
        __metadata('design:type', Object)
    ], ProjectEffects.prototype, "deleteProject$", void 0);
    ProjectEffects = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["b" /* Actions */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["b" /* Actions */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_4__project_service__["a" /* ProjectService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__project_service__["a" /* ProjectService */]) === 'function' && _b) || Object])
    ], ProjectEffects);
    return ProjectEffects;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project.effects.js.map

/***/ },

/***/ 623:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__project_actions__ = __webpack_require__(122);
/* harmony export (immutable) */ exports["a"] = projectReducer;

var initialState = {
    projects: []
};
function projectReducer(state, action) {
    if (state === void 0) { state = initialState; }
    switch (action.type) {
        case __WEBPACK_IMPORTED_MODULE_0__project_actions__["c" /* ActionTypes */].CREATE_PROJECT: {
            return {
                projects: state.projects.concat([action.payload])
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__project_actions__["c" /* ActionTypes */].CREATE_PROJECT_SUCCESS: {
            return {
                projects: state.projects.map(function (project) {
                    if (!project.id && action.payload.id) {
                        return Object.assign({}, project, action.payload);
                    }
                    return project;
                })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__project_actions__["c" /* ActionTypes */].UPDATE_PROJECT: {
            return {
                projects: state.projects.map(function (project) {
                    // check if the updated project has the same id as the current assignemnt
                    if (project.id === action.payload.id) {
                        return Object.assign({}, project, action.payload);
                    }
                    return project;
                })
            };
        }
        // just return the same projects for now since we already updated the store
        case __WEBPACK_IMPORTED_MODULE_0__project_actions__["c" /* ActionTypes */].UPDATE_PROJECT_SUCCESS: {
            return {
                projects: state.projects.map(function (project) {
                    if (project.id === action.payload.id) {
                        return Object.assign({}, project, action.payload);
                    }
                    return project;
                })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__project_actions__["c" /* ActionTypes */].DELETE_PROJECT: {
            return {
                projects: state.projects.filter(function (project) { return project.id !== action.payload.id; })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__project_actions__["c" /* ActionTypes */].LOAD_PROJECTS: {
            return {
                projects: []
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__project_actions__["c" /* ActionTypes */].LOAD_PROJECTS_SUCCESS: {
            return {
                projects: action.payload ? action.payload : []
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__project_actions__["c" /* ActionTypes */].MOVE_PROJECT_ASSIGNMENT: {
            return {
                projects: state.projects.map(function (project) {
                    if (project.id === action.payload.newProjectId) {
                    }
                })
            };
        }
        default: {
            return state;
        }
    }
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project.reducer.js.map

/***/ },

/***/ 624:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return ProjectsComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

var ProjectsComponent = (function () {
    function ProjectsComponent() {
    }
    ProjectsComponent.prototype.ngOnInit = function () {
    };
    ProjectsComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-projects',
            template: __webpack_require__(851),
            styles: [__webpack_require__(816)]
        }), 
        __metadata('design:paramtypes', [])
    ], ProjectsComponent);
    return ProjectsComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/projects.component.js.map

/***/ },

/***/ 625:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__app_actions__ = __webpack_require__(54);
/* harmony export (immutable) */ exports["a"] = reducer;

var initialState = {
    loading: false,
    assignments: []
};
function reducer(state, action) {
    if (state === void 0) { state = initialState; }
    switch (action.type) {
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].CREATE_ASSIGNMENT: {
            return {
                loading: state.loading,
                assignments: state.assignments.concat([action.payload])
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].CREATE_ASSIGNMENT_SUCCESS: {
            var assignmentId_1 = action.payload.id ? Number(action.payload.id) : null;
            return {
                loading: state.loading,
                assignments: state.assignments.map(function (assignment) {
                    if (!assignment.id && assignmentId_1) {
                        return Object.assign({}, assignment, { id: assignmentId_1 });
                    }
                    return assignment;
                })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].CREATE_CRITIQUE_ASSIGNMENT: {
            return state;
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].CREATE_CRITIQUE_ASSIGNMENT_SUCCESS: {
            return {
                loading: state.loading,
                assignments: state.assignments.concat([action.payload])
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].UPDATE_ASSIGNMENT: {
            return {
                loading: state.loading,
                assignments: state.assignments.map(function (assignment) {
                    // check if the updated assignment has the same id as the current assignemnt
                    if (assignment.id === action.payload.id) {
                        return Object.assign({}, assignment, action.payload);
                    }
                    return assignment;
                })
            };
        }
        // just return the same assignments for now since we already updated the store
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].UPDATE_ASSIGNMENT_SUCCESS: {
            return {
                loading: state.loading,
                assignments: state.assignments.map(function (assignment) {
                    if (assignment.id === action.payload.id) {
                        return Object.assign({}, assignment, action.payload);
                    }
                    return assignment;
                })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].DELETE_ASSIGNMENT: {
            return {
                loading: false,
                assignments: state.assignments.filter(function (assignment) { return assignment.id !== action.payload.id; })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].LOAD_ASSIGNMENTS: {
            return {
                loading: true,
                assignments: []
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].LOAD_ASSIGNMENTS_SUCCESS: {
            return {
                loading: false,
                assignments: action.payload ? action.payload : []
            };
        }
        default: {
            return state;
        }
    }
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignments.js.map

/***/ },

/***/ 626:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__app_actions__ = __webpack_require__(54);
/* harmony export (immutable) */ exports["a"] = reducer;

var initialState = {
    permissions: [],
    token: null,
    uid: null
};
function reducer(state, action) {
    if (state === void 0) { state = initialState; }
    switch (action.type) {
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].LOAD_PERMISSIONS: {
            return state;
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["g" /* ActionTypes */].LOAD_PERMISSIONS_SUCCESS: {
            return {
                permissions: action.payload.permissions ? action.payload.permissions : [],
                token: action.payload.token ? action.payload.token : null,
                uid: action.payload.uid ? action.payload.uid : null
            };
        }
        default: {
            return state;
        }
    }
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/users.js.map

/***/ },

/***/ 627:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionCritiqueFormComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

var SubmissionCritiqueFormComponent = (function () {
    function SubmissionCritiqueFormComponent() {
    }
    SubmissionCritiqueFormComponent.prototype.ngOnInit = function () {
    };
    SubmissionCritiqueFormComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-critique-form',
            template: __webpack_require__(853),
            styles: [__webpack_require__(818)]
        }), 
        __metadata('design:paramtypes', [])
    ], SubmissionCritiqueFormComponent);
    return SubmissionCritiqueFormComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-critique-form.component.js.map

/***/ },

/***/ 628:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__submission__ = __webpack_require__(96);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__elmsln_service__ = __webpack_require__(38);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionDetailComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};



var SubmissionDetailComponent = (function () {
    function SubmissionDetailComponent(elmslnService) {
        this.elmslnService = elmslnService;
    }
    SubmissionDetailComponent.prototype.ngOnInit = function () {
    };
    SubmissionDetailComponent.prototype.ngAfterViewInit = function () {
        this.elmslnService.exportLifecycleHook('submissionDetailComponentInit');
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__submission__["a" /* Submission */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__submission__["a" /* Submission */]) === 'function' && _a) || Object)
    ], SubmissionDetailComponent.prototype, "submission", void 0);
    SubmissionDetailComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-detail',
            template: __webpack_require__(854),
            styles: [__webpack_require__(819)]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */]) === 'function' && _b) || Object])
    ], SubmissionDetailComponent);
    return SubmissionDetailComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-detail.component.js.map

/***/ },

/***/ 629:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__submission__ = __webpack_require__(96);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionEditStatesComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};


var SubmissionEditStatesComponent = (function () {
    function SubmissionEditStatesComponent() {
    }
    SubmissionEditStatesComponent.prototype.ngOnInit = function () {
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__submission__["a" /* Submission */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__submission__["a" /* Submission */]) === 'function' && _a) || Object)
    ], SubmissionEditStatesComponent.prototype, "submission", void 0);
    SubmissionEditStatesComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-edit-states',
            template: __webpack_require__(856),
            styles: [__webpack_require__(821)]
        }), 
        __metadata('design:paramtypes', [])
    ], SubmissionEditStatesComponent);
    return SubmissionEditStatesComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-edit-states.component.js.map

/***/ },

/***/ 630:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(16);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__user_service__ = __webpack_require__(171);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionListComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};



var SubmissionListComponent = (function () {
    function SubmissionListComponent(router, userService) {
        this.router = router;
        this.userService = userService;
    }
    SubmissionListComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.userService.getCurrentUserId()
            .subscribe(function (uid) { return _this.currentUserId = uid; });
    };
    SubmissionListComponent.prototype.ngOnChanges = function () {
    };
    SubmissionListComponent.prototype.onSubmissionClick = function (submission) {
        this.router.navigate(['/submissions/' + submission.id]);
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', Array)
    ], SubmissionListComponent.prototype, "submissions", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', String)
    ], SubmissionListComponent.prototype, "title", void 0);
    SubmissionListComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-list',
            template: __webpack_require__(859),
            styles: [__webpack_require__(824)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__user_service__["a" /* UserService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__user_service__["a" /* UserService */]) === 'function' && _b) || Object])
    ], SubmissionListComponent);
    return SubmissionListComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-list.component.js.map

/***/ },

/***/ 631:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__ = __webpack_require__(182);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__ = __webpack_require__(168);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__submission_actions__ = __webpack_require__(80);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__app_actions__ = __webpack_require__(54);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__submission_service__ = __webpack_require__(170);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return SubmissionEffects; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};






var SubmissionEffects = (function () {
    function SubmissionEffects(actions$, submissionService) {
        var _this = this;
        this.actions$ = actions$;
        this.submissionService = submissionService;
        this.createSubmission$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["d" /* ActionTypes */].CREATE_SUBMISSION)
            .mergeMap(function (action) { return _this.submissionService.createSubmission(action.payload); })
            .mergeMap(function (sub) { return _this.submissionService.getSubmission(sub.id); })
            .map(function (sub) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["e" /* createSubmissionSuccess */])(sub); });
        // Update the submission on the server
        this.updateSubmission$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["d" /* ActionTypes */].UPDATE_SUBMISSION)
            .mergeMap(function (action) {
            return _this.submissionService.updateSubmission(action.payload)
                .mergeMap(function (data) {
                return _this.submissionService.getSubmission(action.payload.id);
            });
        })
            .map(function (submission) {
            return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["f" /* updateSubmissionSuccess */])(submission);
        });
        this.loadSubmissions$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["d" /* ActionTypes */].LOAD_SUBMISSIONS)
            .mergeMap(function () { return _this.submissionService.loadSubmissions(); })
            .map(function (submissions) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["g" /* loadSubmissionsSuccess */])(submissions); });
        this.deleteSubmission$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["d" /* ActionTypes */].DELETE_SUBMISSION)
            .mergeMap(function (action) { return _this.submissionService.deleteSubmission(action.payload); })
            .map(function (info) {
            Materialize.toast('Submission deleted', 1000);
        });
        this.notifyAssignmentOnChange$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["d" /* ActionTypes */].CREATE_SUBMISSION_SUCCESS, __WEBPACK_IMPORTED_MODULE_3__submission_actions__["d" /* ActionTypes */].UPDATE_SUBMISSION_SUCCESS)
            .map(function (action) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__app_actions__["b" /* loadAssignments */])(); });
    }
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], SubmissionEffects.prototype, "createSubmission$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], SubmissionEffects.prototype, "updateSubmission$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], SubmissionEffects.prototype, "loadSubmissions$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])({ dispatch: false }), 
        __metadata('design:type', Object)
    ], SubmissionEffects.prototype, "deleteSubmission$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], SubmissionEffects.prototype, "notifyAssignmentOnChange$", void 0);
    SubmissionEffects = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["b" /* Actions */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["b" /* Actions */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_5__submission_service__["a" /* SubmissionService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_5__submission_service__["a" /* SubmissionService */]) === 'function' && _b) || Object])
    ], SubmissionEffects);
    return SubmissionEffects;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.effects.js.map

/***/ },

/***/ 632:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__submission_actions__ = __webpack_require__(80);
/* harmony export (immutable) */ exports["a"] = submissionReducer;

var initialState = {
    saving: false,
    savingImage: false,
    submissions: []
};
function submissionReducer(state, action) {
    if (state === void 0) { state = initialState; }
    switch (action.type) {
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].CREATE_SUBMISSION: {
            return {
                saving: true,
                savingImage: state.savingImage,
                submissions: state.submissions.concat([action.payload])
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].CREATE_SUBMISSION_SUCCESS: {
            return {
                saving: false,
                savingImage: state.savingImage,
                submissions: state.submissions.map(function (submission) {
                    if (!submission.id && action.payload.id) {
                        return Object.assign({}, submission, action.payload);
                    }
                    return submission;
                })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].UPDATE_SUBMISSION: {
            return {
                saving: true,
                savingImage: state.savingImage,
                submissions: state.submissions.map(function (submission) {
                    // check if the updated submission has the same id as the current assignemnt
                    if (submission.id === action.payload.id) {
                        return Object.assign({}, submission, action.payload);
                    }
                    return submission;
                })
            };
        }
        // just return the same submissions for now since we already updated the store
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].UPDATE_SUBMISSION_SUCCESS: {
            return {
                saving: false,
                savingImage: state.savingImage,
                submissions: state.submissions.map(function (submission) {
                    if (submission.id === action.payload.id) {
                        return Object.assign({}, submission, action.payload);
                    }
                    return submission;
                })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].DELETE_SUBMISSION: {
            console.log(state.submissions, action.payload);
            return {
                saving: state.saving,
                savingImage: state.savingImage,
                submissions: state.submissions.filter(function (submission) { return submission.id !== action.payload.id; })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].LOAD_SUBMISSIONS: {
            return {
                saving: state.saving,
                savingImage: state.savingImage,
                submissions: []
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].LOAD_SUBMISSIONS_SUCCESS: {
            return {
                saving: state.saving,
                savingImage: state.savingImage,
                submissions: action.payload ? action.payload : []
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].CREATE_SUBMISSION_IMAGE: {
            return {
                saving: state.saving,
                savingImage: true,
                submissions: state.submissions
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].CREATE_SUBMISSION_IMAGE_SUCCESS: {
            return {
                saving: state.saving,
                savingImage: false,
                submissions: state.submissions
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].CREATE_SUBMISSION_IMAGE_FAILURE: {
            return {
                saving: state.saving,
                savingImage: false,
                submissions: state.submissions
            };
        }
        default: {
            return state;
        }
    }
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.reducer.js.map

/***/ },

/***/ 633:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return UserComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

var UserComponent = (function () {
    function UserComponent() {
        this.username = 'restws_admin';
        this.password = 'admin';
    }
    UserComponent.prototype.ngOnInit = function () {
    };
    UserComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'cle-user',
            template: __webpack_require__(862),
            styles: [__webpack_require__(826)]
        }), 
        __metadata('design:paramtypes', [])
    ], UserComponent);
    return UserComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/user.component.js.map

/***/ },

/***/ 634:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(77);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__elmsln_service__ = __webpack_require__(38);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return WysiwygjsComponent; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};



var WysiwygjsComponent = (function () {
    function WysiwygjsComponent(el, elmslnService) {
        this.el = el;
        this.elmslnService = elmslnService;
        this.onWysiwygInit = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.onContentUpdate = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.onImageSave = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.propagateChange = function (_) { };
    }
    //ControlValueAccessor
    WysiwygjsComponent.prototype.writeValue = function (value) {
        this.content = value;
        this.updateContent();
    };
    WysiwygjsComponent.prototype.registerOnChange = function (fn) {
        this.propagateChange = fn;
    };
    WysiwygjsComponent.prototype.registerOnTouched = function () {
    };
    WysiwygjsComponent.prototype.ngOnInit = function () {
        var newThis = this;
        jQuery(this.el.nativeElement.firstElementChild).each(function (index, element) {
            var wysiwygEditor = jQuery(element).wysiwyg({
                // 'selection'|'top'|'top-selection'|'bottom'|'bottom-selection'
                toolbar: 'top',
                buttons: {
                    insertimage: {
                        title: 'Insert image',
                        image: '\uf030',
                        //showstatic: true,    // wanted on the toolbar
                        showselection: false // wanted on selection
                    },
                    insertvideo: {
                        title: 'Insert video',
                        image: '\uf03d',
                        //showstatic: true,    // wanted on the toolbar
                        showselection: false // wanted on selection
                    },
                    insertlink: {
                        title: 'Insert link',
                        image: '\uf08e' // <img src="path/to/image.png" width="16" height="16" alt="" />
                    },
                    // Fontname plugin
                    //   fontname: {
                    //       title: 'Font',
                    //       image: '\uf031', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       popup: function ($popup, $button) {
                    //           var list_fontnames = {
                    //               // Name : Font
                    //               'Arial, Helvetica': 'Arial,Helvetica',
                    //               'Verdana': 'Verdana,Geneva',
                    //               'Georgia': 'Georgia',
                    //               'Courier New': 'Courier New,Courier',
                    //               'Times New Roman': 'Times New Roman,Times'
                    //           };
                    //           var $list = $('<div/>').addClass('wysiwyg-plugin-list')
                    //               .attr('unselectable', 'on');
                    //           $.each(list_fontnames, function (name, font) {
                    //               var $link = $('<a/>').attr('href', '#')
                    //                   .css('font-family', font)
                    //                   .html(name)
                    //                   .click(function (event) {
                    //                       (<any>$(element)).wysiwyg('shell').fontName(font).closePopup();
                    //                       // prevent link-href-#
                    //                       event.stopPropagation();
                    //                       event.preventDefault();
                    //                       return false;
                    //                   });
                    //               $list.append($link);
                    //           });
                    //           $popup.append($list);
                    //       },
                    //       //showstatic: true,    // wanted on the toolbar
                    //       showselection: index == 0 ? true : false    // wanted on selection
                    //   },
                    //   // Fontsize plugin
                    //   fontsize: {
                    //       title: 'Size',
                    //       image: '\uf034', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       popup: function ($popup, $button) {
                    //           // Hack: http://stackoverflow.com/questions/5868295/document-execcommand-fontsize-in-pixels/5870603#5870603
                    //           var list_fontsizes = [];
                    //           for (var i = 8; i <= 11; ++i)
                    //               list_fontsizes.push(i + 'px');
                    //           for (var i = 12; i <= 28; i += 2)
                    //               list_fontsizes.push(i + 'px');
                    //           list_fontsizes.push('36px');
                    //           list_fontsizes.push('48px');
                    //           list_fontsizes.push('72px');
                    //           var $list = $('<div/>').addClass('wysiwyg-plugin-list')
                    //               .attr('unselectable', 'on');
                    //           $.each(list_fontsizes, function (index, size) {
                    //               var $link = $('<a/>').attr('href', '#')
                    //                   .html(size)
                    //                   .click(function (event) {
                    //                       (<any>$(element)).wysiwyg('shell').fontSize(7).closePopup();
                    //                       (<any>$(element)).wysiwyg('container')
                    //                           .find('font[size=7]')
                    //                           .removeAttr("size")
                    //                           .css("font-size", size);
                    //                       // prevent link-href-#
                    //                       event.stopPropagation();
                    //                       event.preventDefault();
                    //                       return false;
                    //                   });
                    //               $list.append($link);
                    //           });
                    //           $popup.append($list);
                    //       },
                    //       showselection: true    // wanted on selection
                    //   },
                    // Header plugin
                    header: {
                        title: 'Header',
                        image: '\uf1dc',
                        popup: function ($popup, $button) {
                            var list_headers = {
                                // Name : Font
                                'Header 1': '<h1>',
                                'Header 2': '<h2>',
                                'Header 3': '<h3>',
                                'Header 4': '<h4>',
                                'Header 5': '<h5>',
                                'Header 6': '<h6>',
                                'Code': '<pre>'
                            };
                            var $list = jQuery('<div/>').addClass('wysiwyg-plugin-list')
                                .attr('unselectable', 'on');
                            jQuery.each(list_headers, function (name, format) {
                                var $link = jQuery('<a/>').attr('href', '#')
                                    .css('font-family', format)
                                    .html(name)
                                    .click(function (event) {
                                    jQuery(element).wysiwyg('shell').format(format).closePopup();
                                    // prevent link-href-#
                                    event.stopPropagation();
                                    event.preventDefault();
                                    return false;
                                });
                                $list.append($link);
                            });
                            $popup.append($list);
                        }
                    },
                    bold: {
                        title: 'Bold (Ctrl+B)',
                        image: '\uf032',
                        hotkey: 'b'
                    },
                    italic: {
                        title: 'Italic (Ctrl+I)',
                        image: '\uf033',
                        hotkey: 'i'
                    },
                    underline: {
                        title: 'Underline (Ctrl+U)',
                        image: '\uf0cd',
                        hotkey: 'u'
                    },
                    strikethrough: {
                        title: 'Strikethrough (Ctrl+S)',
                        image: '\uf0cc',
                        hotkey: 's'
                    },
                    //   forecolor: {
                    //       title: 'Text color',
                    //       image: '\uf1fc' // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //   },
                    //   highlight: {
                    //       title: 'Background color',
                    //       image: '\uf043' // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //   },
                    //   alignleft: index != 0 ? false : {
                    //       title: 'Left',
                    //       image: '\uf036', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       //showstatic: true,    // wanted on the toolbar
                    //       showselection: false    // wanted on selection
                    //   },
                    //   aligncenter: index != 0 ? false : {
                    //       title: 'Center',
                    //       image: '\uf037', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       //showstatic: true,    // wanted on the toolbar
                    //       showselection: false    // wanted on selection
                    //   },
                    //   alignright: index != 0 ? false : {
                    //       title: 'Right',
                    //       image: '\uf038', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       //showstatic: true,    // wanted on the toolbar
                    //       showselection: false    // wanted on selection
                    //   },
                    //   alignjustify: index != 0 ? false : {
                    //       title: 'Justify',
                    //       image: '\uf039', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       //showstatic: true,    // wanted on the toolbar
                    //       showselection: false    // wanted on selection
                    //   },
                    //   subscript: index == 1 ? false : {
                    //       title: 'Subscript',
                    //       image: '\uf12c', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       //showstatic: true,    // wanted on the toolbar
                    //       showselection: true    // wanted on selection
                    //   },
                    //   superscript: index == 1 ? false : {
                    //       title: 'Superscript',
                    //       image: '\uf12b', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       //showstatic: true,    // wanted on the toolbar
                    //       showselection: true    // wanted on selection
                    //   },
                    //   indent: index != 0 ? false : {
                    //       title: 'Indent',
                    //       image: '\uf03c', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       //showstatic: true,    // wanted on the toolbar
                    //       showselection: false    // wanted on selection
                    //   },
                    //   outdent: index != 0 ? false : {
                    //       title: 'Outdent',
                    //       image: '\uf03b', // <img src="path/to/image.png" width="16" height="16" alt="" />
                    //       //showstatic: true,    // wanted on the toolbar
                    //       showselection: false    // wanted on selection
                    //   },
                    orderedList: index != 0 ? false : {
                        title: 'Ordered list',
                        image: '\uf0cb',
                        //showstatic: true,    // wanted on the toolbar
                        showselection: false // wanted on selection
                    },
                    unorderedList: index != 0 ? false : {
                        title: 'Unordered list',
                        image: '\uf0ca',
                        //showstatic: true,    // wanted on the toolbar
                        showselection: false // wanted on selection
                    },
                    removeformat: {
                        title: 'Remove format',
                        image: '\uf12d' // <img src="path/to/image.png" width="16" height="16" alt="" />
                    }
                },
                // Other properties
                selectImage: 'Click to upload image',
                placeholderUrl: 'www.example.com',
                placeholderEmbed: '<embed/>',
                maxImageSize: [1024, 640],
                onImageUpload: function (insert_image) {
                },
                forceImageUpload: false,
                videoFromUrl: function (url) {
                    // Contributions are welcome :-)
                    // youtube - http://stackoverflow.com/questions/3392993/php-regex-to-get-youtube-video-id
                    var youtube_match = url.match(/^(?:http(?:s)?:\/\/)?(?:[a-z0-9.]+\.)?(?:youtu\.be|youtube\.com)\/(?:(?:watch)?\?(?:.*&)?v(?:i)?=|(?:embed|v|vi|user)\/)([^\?&\"'>]+)/);
                    if (youtube_match && youtube_match[1].length == 11)
                        return '<iframe src="//www.youtube.com/embed/' + youtube_match[1] + '" width="640" height="360" frameborder="0" allowfullscreen></iframe>';
                    // vimeo - http://embedresponsively.com/
                    var vimeo_match = url.match(/^(?:http(?:s)?:\/\/)?(?:[a-z0-9.]+\.)?vimeo\.com\/([0-9]+)$/);
                    if (vimeo_match)
                        return '<iframe src="//player.vimeo.com/video/' + vimeo_match[1] + '" width="640" height="360" frameborder="0" webkitAllowFullScreen mozallowfullscreen allowFullScreen></iframe>';
                    // dailymotion - http://embedresponsively.com/
                    var dailymotion_match = url.match(/^(?:http(?:s)?:\/\/)?(?:[a-z0-9.]+\.)?dailymotion\.com\/video\/([0-9a-z]+)$/);
                    if (dailymotion_match)
                        return '<iframe src="//www.dailymotion.com/embed/video/' + dailymotion_match[1] + '" width="640" height="360" frameborder="0" webkitAllowFullScreen mozallowfullscreen allowFullScreen></iframe>';
                    // undefined -> create '<video/>' tag
                }
            });
        })
            .change(function () {
            // Assign the wysiwyg get contents to the content Observable
            // emit the change
            var target = jQuery(newThis.el.nativeElement).find('.wysiwyg-editor');
            target.find('img:not(.processed)').each(function (index, value) {
                var _this = this;
                var base64 = jQuery(this).attr('src');
                newThis.onImageSave.emit({ type: 'saving' });
                newThis.uploadImage(base64)
                    .subscribe(function (image) {
                    jQuery(_this).attr('src', image.url);
                    jQuery(_this).attr('width', image.metadata.width);
                    jQuery(_this).attr('height', image.metadata.height);
                    jQuery(_this).addClass('processed');
                    newThis.onImageSave.emit({
                        type: 'success',
                        image: image
                    });
                }, function (error) {
                    jQuery(_this).remove();
                    newThis.onImageSave.emit({
                        type: 'error'
                    });
                });
                // .subscribe(url => {
                //     jQuery(this).attr('src', url).addClass('processed');
                //     console.log(url);
                //     return;
                // })
            });
            // Update content
            newThis.content = target.html();
            newThis.propagateChange(newThis.content);
            newThis.onContentUpdate.emit();
        });
        this.onWysiwygInit.emit();
    };
    WysiwygjsComponent.prototype.updateContent = function () {
        jQuery(this.el.nativeElement).find('.wysiwyg-editor').html(this.content);
    };
    /**
     * @todo: not ready yet
     */
    WysiwygjsComponent.prototype.resizeImage = function (data) {
        var image = new Image();
        image.src = data;
        var resize_canvas = document.createElement('canvas');
        resize_canvas.width = 800;
        resize_canvas.height = 800;
        resize_canvas.getContext('2d').drawImage(image, 0, 0, 800, 800);
        return resize_canvas.toDataURL("image/jpg");
    };
    WysiwygjsComponent.prototype.uploadImage = function (base64) {
        /**
         * @todo: need to actually upload this to the server
         */
        return this.elmslnService.createImage(base64)
            .map(function (data) { return data; });
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', String)
    ], WysiwygjsComponent.prototype, "content", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _a) || Object)
    ], WysiwygjsComponent.prototype, "onWysiwygInit", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _b) || Object)
    ], WysiwygjsComponent.prototype, "onContentUpdate", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Output"])(), 
        __metadata('design:type', (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]) === 'function' && _c) || Object)
    ], WysiwygjsComponent.prototype, "onImageSave", void 0);
    WysiwygjsComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'wysiwygjs',
            template: __webpack_require__(863),
            styles: [__webpack_require__(827)],
            providers: [
                {
                    provide: __WEBPACK_IMPORTED_MODULE_1__angular_forms__["d" /* NG_VALUE_ACCESSOR */],
                    useExisting: __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["forwardRef"])(function () { return WysiwygjsComponent; }),
                    multi: true
                }
            ]
        }), 
        __metadata('design:paramtypes', [(typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */]) === 'function' && _e) || Object])
    ], WysiwygjsComponent);
    return WysiwygjsComponent;
    var _a, _b, _c, _d, _e;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/wysiwygjs.component.js.map

/***/ },

/***/ 635:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return environment; });
// The file contents for the current environment will overwrite these during build.
// The build system defaults to the dev environment which uses `environment.ts`, but if you do
// `ng build --env=prod` then `environment.prod.ts` will be used instead.
// The list of which env maps to which file can be found in `angular-cli.json`.
var environment = {
    production: false
};
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/environment.js.map

/***/ },

/***/ 636:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_core_js_es6_symbol__ = __webpack_require__(652);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_core_js_es6_symbol___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_core_js_es6_symbol__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_core_js_es6_object__ = __webpack_require__(645);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_core_js_es6_object___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_core_js_es6_object__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_core_js_es6_function__ = __webpack_require__(641);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_core_js_es6_function___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_core_js_es6_function__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_core_js_es6_parse_int__ = __webpack_require__(647);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_core_js_es6_parse_int___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3_core_js_es6_parse_int__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4_core_js_es6_parse_float__ = __webpack_require__(646);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4_core_js_es6_parse_float___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_4_core_js_es6_parse_float__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5_core_js_es6_number__ = __webpack_require__(644);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5_core_js_es6_number___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_5_core_js_es6_number__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6_core_js_es6_math__ = __webpack_require__(643);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6_core_js_es6_math___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_6_core_js_es6_math__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7_core_js_es6_string__ = __webpack_require__(651);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7_core_js_es6_string___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_7_core_js_es6_string__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8_core_js_es6_date__ = __webpack_require__(640);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8_core_js_es6_date___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_8_core_js_es6_date__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9_core_js_es6_array__ = __webpack_require__(639);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9_core_js_es6_array___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_9_core_js_es6_array__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10_core_js_es6_regexp__ = __webpack_require__(649);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10_core_js_es6_regexp___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_10_core_js_es6_regexp__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11_core_js_es6_map__ = __webpack_require__(642);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11_core_js_es6_map___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_11_core_js_es6_map__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12_core_js_es6_set__ = __webpack_require__(650);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12_core_js_es6_set___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_12_core_js_es6_set__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_13_core_js_es6_reflect__ = __webpack_require__(648);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_13_core_js_es6_reflect___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_13_core_js_es6_reflect__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_14_core_js_es7_reflect__ = __webpack_require__(653);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_14_core_js_es7_reflect___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_14_core_js_es7_reflect__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_15_zone_js_dist_zone__ = __webpack_require__(1126);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_15_zone_js_dist_zone___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_15_zone_js_dist_zone__);
















//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/polyfills.js.map

/***/ },

/***/ 67:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngrx_store__ = __webpack_require__(11);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__elmsln_service__ = __webpack_require__(38);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__app_settings__ = __webpack_require__(95);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__assignment__ = __webpack_require__(121);
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AssignmentService; });
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





var AssignmentService = (function () {
    function AssignmentService(elmsln, store) {
        this.elmsln = elmsln;
        this.store = store;
        this.assignments = this.store.select(function (state) { return state.assignments; });
    }
    AssignmentService.prototype.getAssignments = function (projectId) {
        var _this = this;
        var query = projectId ? '?project=' + projectId : '';
        this.elmsln.get(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments' + query)
            .map(function (data) { return data.json(); })
            .map(function (data) { return typeof data.data !== 'undefined' ? data.data : []; })
            .map(function (data) {
            if (data) {
                // convert list of data into list of Assignments
                var d_1 = [];
                data.forEach(function (item) { return d_1.push(_this.convertToAssignment(item)); });
                return d_1;
            }
        })
            .map(function (payload) { return ({ type: 'ADD_ASSIGNMENTS', payload: payload }); })
            .subscribe(function (action) { return _this.store.dispatch(action); });
    };
    AssignmentService.prototype.loadAssignments = function () {
        var _this = this;
        return this.elmsln.get(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments')
            .map(function (data) { return data.json().data; })
            .map(function (data) {
            if (data) {
                // convert list of data into list of Assignments
                var d_2 = [];
                data.forEach(function (item) { return d_2.push(_this.convertToAssignment(item)); });
                return d_2;
            }
        });
    };
    AssignmentService.prototype.getAssignment = function (assignmentId) {
        var _this = this;
        return this.elmsln.get(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments/' + assignmentId)
            .map(function (data) { return data.json().data[0]; })
            .map(function (data) { return _this.convertToAssignment(data); });
    };
    AssignmentService.prototype.createAssignment = function (assignment) {
        var newAssignment = this.prepareForDrupal(assignment);
        return this.elmsln.post(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments/create', newAssignment)
            .map(function (data) { return data.json().node; })
            .map(function (node) { return Number(node.nid); });
    };
    AssignmentService.prototype.updateAssignment = function (assignment) {
        var _this = this;
        var newAssignment = this.prepareForDrupal(assignment);
        return this.elmsln.put(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments/' + assignment.id + '/update', newAssignment)
            .map(function (data) { return data.json().node; })
            .map(function (node) { return _this.convertToAssignment(node); });
    };
    AssignmentService.prototype.deleteAssignment = function (assignment) {
        return this.elmsln.delete(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments/' + assignment.id + '/delete')
            .map(function (data) { return data.json(); });
    };
    AssignmentService.prototype.startCritique = function (assignment) {
        return this.elmsln.get(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments/' + assignment.id + '/critique')
            .map(function (data) { return data.json(); });
    };
    /**
     * @todo: this should eventually be more dynamic
     */
    AssignmentService.prototype.getAssignmentOptions = function () {
        return {
            type: [
                { value: 'open', display: 'Open' },
                { value: 'open_after_submission', display: 'Open After Submission' },
                { value: 'closed', display: 'Closed' }
            ],
            critiqueMethod: [
                { value: 'none', display: 'None' },
                { value: 'open', display: 'Open' },
                { value: 'random', display: 'Random' }
            ],
            critiqueStyle: [
                { value: 'open', display: 'Open' },
                { value: 'blind', display: 'Blind' },
                { value: 'double_blind', display: 'Double blind' }
            ]
        };
    };
    AssignmentService.prototype.convertToAssignment = function (data) {
        var converted = new __WEBPACK_IMPORTED_MODULE_4__assignment__["a" /* Assignment */]();
        for (var propertyName in converted) {
            if (data[propertyName]) {
                converted[propertyName] = data[propertyName];
            }
        }
        if (data['hierarchy']) {
            if (data['hierarchy']['project']) {
                converted['project'] = Number(data['hierarchy']['project']);
            }
        }
        if (data['evidence']) {
            if (data['evidence']['critique']) {
                if (data['evidence']['critique']['method']) {
                    converted.critiqueMethod = data['evidence']['critique']['method'];
                }
                if (data['evidence']['critique']['public']) {
                    converted.critiquePrivacy = data['evidence']['critique']['public'];
                }
            }
        }
        return converted;
    };
    AssignmentService.prototype.prepareForDrupal = function (assignment) {
        // Convert date fields
        var newAssignment = Object.assign({}, assignment);
        // remove created
        delete newAssignment.created;
        if (assignment.body) {
            newAssignment.body = {
                value: assignment.body,
                format: 'textbook_editor'
            };
        }
        if (assignment.type) {
            Object.assign(newAssignment, assignment.type);
        }
        Object.assign(newAssignment, { evidence: { critique: {
                    method: assignment.critiqueMethod,
                    public: assignment.critiquePrivacy ? 1 : 0
                } } });
        var dateFields = ['startDate', 'endDate'];
        dateFields.forEach(function (field) {
            if (assignment[field]) {
                assignment[field] = (Date.parse(assignment[field]) / 1000);
                assignment[field] = assignment[field].toString();
            }
        });
        // the due date works weird so we need to do some custom logic to find out what field to populate
        // in Drupal
        if (assignment.endDate !== null) {
            if (assignment.startDate !== null) {
                newAssignment.startDate = assignment.startDate,
                    newAssignment.endDate = assignment.endDate;
            }
            else {
                newAssignment.startDate = assignment.endDate;
                newAssignment.endDate = null;
            }
        }
        return newAssignment;
    };
    Object.defineProperty(AssignmentService.prototype, "userCanEdit", {
        // Return if the user should be able to edit a project
        get: function () {
            return this.store.select('user')
                .map(function (state) { return state.permissions.includes('edit own cle_assignment content'); });
        },
        enumerable: true,
        configurable: true
    });
    /**
     * Find out if an assignment is a Critique assignment
     */
    AssignmentService.prototype.assignmentIsCritique = function (assignment) {
        if (assignment.hierarchy) {
            if (assignment.hierarchy.dependencies) {
                if (assignment.hierarchy.dependencies.length > 0) {
                    return true;
                }
            }
        }
        return false;
    };
    AssignmentService = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], AssignmentService);
    return AssignmentService;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment.service.js.map

/***/ },

/***/ 794:
/***/ function(module, exports) {

module.exports = ".submission-states ul {\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n  margin: 0;\n  padding: 0;\n  width: 100%;\n  -webkit-box-pack: center;\n      -ms-flex-pack: center;\n          justify-content: center;\n  -webkit-box-align: center;\n      -ms-flex-align: center;\n          align-items: center; }\n\n.submission-states li {\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n  width: 100%;\n  -webkit-box-align: center;\n      -ms-flex-align: center;\n          align-items: center;\n  -webkit-box-pack: center;\n      -ms-flex-pack: center;\n          justify-content: center;\n  max-width: 20em;\n  position: relative;\n  color: #d0d0d0;\n  background: #d0d0d0;\n  height: 3em; }\n  .submission-states li * > {\n    color: black; }\n  .submission-states li:before {\n    position: absolute;\n    content: \"\";\n    top: 0;\n    width: 0;\n    height: 0;\n    z-index: 2;\n    right: -1.48604em;\n    border-top: 1.532em solid transparent;\n    border-bottom: 1.532em solid transparent;\n    border-left: 1.532em solid currentColor; }\n\n.submission-states li:nth-child(2) {\n  background: #c3c3c3; }\n  .submission-states li:nth-child(2):before {\n    border-left-color: #c3c3c3; }\n\n.submission-states li:nth-child(3) {\n  background: #b7b7b7; }\n  .submission-states li:nth-child(3):before {\n    border-left-color: #b7b7b7; }\n\n.submission-states li:nth-child(4) {\n  background: #aaaaaa; }\n  .submission-states li:nth-child(4):before {\n    border-left-color: #aaaaaa; }\n\n.submission-states li.active:before {\n  border-left-color: inherit; }\n\n.submission-states li.canEdit {\n  cursor: pointer; }\n\n.submission-item__container {\n  color: black; }\n"

/***/ },

/***/ 795:
/***/ function(module, exports) {

module.exports = ".cle-critique {\n  margin: 0 calc(-50vw + 50%);\n}\n\n.nav-wrapper {\n  background: #484848;\n  height: 50px;\n}\n.nav-wrapper * {\n  font-size: 14px;\n  height: 50px;\n  line-height: 50px;\n  color: white;\n}"

/***/ },

/***/ 796:
/***/ function(module, exports) {

module.exports = ".assignment {\n  position: relative;\n  background: #e6e6e6;\n  display: block;\n  padding: 1em;\n  font-size: .9em;\n  margin-bottom: 2em;\n  width: 80vw;\n  max-width: 38em;\n  padding-left: 3em;\n  box-shadow: 1px 1px 5px rgba(0, 0, 0, .6);\n }\n.assignment__label {\n  opacity: .5;\n  font-size: 1.3em;\n  margin-top: 0;\n}\n\n.assignment__icon {\n  position: absolute;\n  top: .5em;\n  left: .3em;\n}\n\n.assignment__title {\n  font-size: 1.2em;\n}\n.assignment__body {\n}"

/***/ },

/***/ 797:
/***/ function(module, exports) {

module.exports = ".assignment-dialog {\n  top: 5% !important;\n  bottom: 5% !important;\n  max-height: none !important;\n  height: 90%;\n}"

/***/ },

/***/ 798:
/***/ function(module, exports) {

module.exports = ".assignment-form {\n  max-width: 55em;\n  margin: auto;\n}\n\n.assignment-form > * {\n  margin-top: 2em;\n}\n\n.privacy .label {\n  display: block;\n}\n\n.privacy .detail {\n  padding-top: .5em;\n}\n\n.due-date .display {\n  font-size: 1.2em;\n  text-align: center;\n  margin: 1em;\n  color: gray;\n}\n\n.due-date .separator {\n  margin: 0 .5em;\n}\n\n:host >>> .wysiwyg-editor {\n  min-height: 10em;\n}\n\nselect {\n  display: block;\n}\n\n.fieldset {\n  padding: 1em;\n  padding-top: 2em;\n  background: rgba(0,0,0, 0.07);\n  position: relative;\n}\n.fieldset > * {\n  padding-bottom: 1em;\n}\n.fieldset > label:first-of-type {\n  position: absolute;\n  top: .5em;\n  left: .5em;\n}"

/***/ },

/***/ 799:
/***/ function(module, exports) {

module.exports = ".icon {\n  float: left;\n  margin-right: 1em;\n}\n\n.assignment:hover {\n  cursor: pointer;\n}\n\n.status {\n  float: right;\n  size: .9em;\n}\n@media (min-width: 500px) {\n  .status {\n    position: absolute;\n    top: 50%;\n    -webkit-transform: translateY(-50%);\n            transform: translateY(-50%);\n    right: 1em;\n  }\n}\n\n.status.complete {\n  color: green;\n}\n\n.add-button {\n  position: fixed;\n  top: 3.5em;\n  right: 3em;\n}\n\nnav, nav .btn {\n  background: transparent;\n  box-shadow: none;\n}\nnav li a {\n  color: #2196F3;\n}\n\n.assignment {\n  position: relative;\n}\n\n.assignment--loading {\n  background: #efefef;\n}\n\n.assignment:hover .assignment__edit-buttons {\n  opacity: 1;\n}\n\n.assignment__edit-buttons {\n  position: absolute;\n  right: 0;\n  top: 0;\n  background: -webkit-linear-gradient(left, transparent, white 30%);\n  background: linear-gradient(to right, transparent, white 30%);\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n  -webkit-box-align: center;\n      -ms-flex-align: center;\n          align-items: center;\n  -webkit-box-pack: end;\n      -ms-flex-pack: end;\n          justify-content: flex-end;\n  padding-left: 2em;\n  opacity: 0;\n  -webkit-transition: opacity .3s ease-in-out;\n  transition: opacity .3s ease-in-out;\n}\n\n.assignment__icons {\n  position: absolute;\n  right: 0;\n  top: 0;\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n  -webkit-box-align: center;\n      -ms-flex-align: center;\n          align-items: center;\n  -webkit-box-pack: end;\n      -ms-flex-pack: end;\n          justify-content: flex-end;\n  padding-left: 2em;\n}\n\n.assignment__icon--complete {\n  color: green;\n}"

/***/ },

/***/ 80:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "d", function() { return ActionTypes; });
/* harmony export (immutable) */ exports["b"] = createSubmission;
/* harmony export (immutable) */ exports["e"] = createSubmissionSuccess;
/* harmony export (immutable) */ exports["c"] = updateSubmission;
/* harmony export (immutable) */ exports["f"] = updateSubmissionSuccess;
/* unused harmony export deleteSubmission */
/* harmony export (immutable) */ exports["a"] = loadSubmissions;
/* harmony export (immutable) */ exports["g"] = loadSubmissionsSuccess;
/* unused harmony export loadPermissions */
/* unused harmony export loadPermissionsSuccess */
/* unused harmony export createSubmissionImage */
/* unused harmony export createSubmissionImageSuccess */
/* unused harmony export createSubmissionImageFailure */
var ActionTypes = {
    CREATE_SUBMISSION: 'CREATE_SUBMISSION',
    CREATE_SUBMISSION_SUCCESS: 'CREATE_SUBMISSION_SUCCESS',
    UPDATE_SUBMISSION: 'UPDATE_SUBMISSION',
    UPDATE_SUBMISSION_SUCCESS: 'UPDATE_SUBMISSION_SUCCESS',
    DELETE_SUBMISSION: 'DELETE_SUBMISSION',
    LOAD_SUBMISSIONS: 'LOAD_SUBMISSIONS',
    LOAD_SUBMISSIONS_SUCCESS: 'LOAD_SUBMISSIONS_SUCCESS',
    LOAD_PERMISSIONS: 'LOAD_PERMISSIONS',
    LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS',
    CREATE_SUBMISSION_IMAGE: 'CREATE_SUBMISSION_IMAGE',
    CREATE_SUBMISSION_IMAGE_SUCCESS: 'CREATE_SUBMISSION_IMAGE_SUCCESS',
    CREATE_SUBMISSION_IMAGE_FAILURE: 'CREATE_SUBMISSION_IMAGE_FAILURE'
};
function createSubmission(submission) {
    return {
        type: ActionTypes.CREATE_SUBMISSION,
        payload: submission
    };
}
function createSubmissionSuccess(submission) {
    return {
        type: ActionTypes.CREATE_SUBMISSION_SUCCESS,
        payload: submission
    };
}
function updateSubmission(submission) {
    return {
        type: ActionTypes.UPDATE_SUBMISSION,
        payload: submission
    };
}
function updateSubmissionSuccess(submission) {
    return {
        type: ActionTypes.UPDATE_SUBMISSION_SUCCESS,
        payload: submission
    };
}
function deleteSubmission(submission) {
    return {
        type: ActionTypes.DELETE_SUBMISSION,
        payload: submission
    };
}
function loadSubmissions() {
    return {
        type: ActionTypes.LOAD_SUBMISSIONS,
        payload: {}
    };
}
function loadSubmissionsSuccess(submissions) {
    return {
        type: ActionTypes.LOAD_SUBMISSIONS_SUCCESS,
        payload: submissions
    };
}
function loadPermissions() {
    return {
        type: ActionTypes.LOAD_PERMISSIONS,
        payload: {}
    };
}
function loadPermissionsSuccess(permissions) {
    return {
        type: ActionTypes.LOAD_PERMISSIONS_SUCCESS,
        payload: permissions
    };
}
function createSubmissionImage() {
    return {
        type: ActionTypes.CREATE_SUBMISSION_IMAGE,
        payload: {}
    };
}
function createSubmissionImageSuccess() {
    return {
        type: ActionTypes.CREATE_SUBMISSION_IMAGE_SUCCESS,
        payload: {}
    };
}
function createSubmissionImageFailure() {
    return {
        type: ActionTypes.CREATE_SUBMISSION_IMAGE_FAILURE,
        payload: {}
    };
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.actions.js.map

/***/ },

/***/ 800:
/***/ function(module, exports) {

module.exports = ".assignment__rationale {\n  padding: .1em .5em;\n  background-color: lightgray;\n  font-size: .9em;\n}\n\n.assignment__actions {\n  margin-top: 3em;\n}"

/***/ },

/***/ 801:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 802:
/***/ function(module, exports) {

module.exports = ":host >>> .wysiwyg-editor {\n  min-height: 200px;\n}\n\n:host >>> .wysiwyg-container {\n  max-width: 900px;\n  margin: 1em;\n}"

/***/ },

/***/ 803:
/***/ function(module, exports) {

module.exports = ".created {\n  font-size: .9em;\n  opacity: .8;\n}\n\n.critique {\n  display: block;\n  overflow: hidden;\n}"

/***/ },

/***/ 804:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 805:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 806:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 807:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 808:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 809:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 810:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 811:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 812:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 813:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 814:
/***/ function(module, exports) {

module.exports = ".project {\n  margin: 1em;\n  padding: 1em;\n  background: lightgray;\n  width: auto;\n  position: relative;\n}\n\n.project__header {\n  position: relative;\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n}\n\n.project__options {\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n}\n.project__options > a {\n}\n\n.project__title-container {\n  width: 100%;\n}\n\n.project__title {\n  margin-top: 0;\n  font-size: 1.4em;\n}\n\n.project__board {\n  padding: 1em;\n  min-height: 200px;\n  width: 100%;\n}\n\n.assignment {\n  background: white;\n  padding: 1em;\n  width: 100%;\n}\n\n.assignment__title {\n  margin-top: 0;\n  font-size: 1.4em;\n}"

/***/ },

/***/ 815:
/***/ function(module, exports) {

module.exports = ".projects-container {\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n  width: auto;\n  -webkit-box-align: center;\n      -ms-flex-align: center;\n          align-items: center;\n  -webkit-box-pack: start;\n      -ms-flex-pack: start;\n          justify-content: flex-start;\n  -webkit-box-align: start;\n      -ms-flex-align: start;\n          align-items: flex-start;\n  overflow-x: scroll;\n  margin: 0 calc(-50vw + 50%);\n}\n\n.projects-container >>> app-project-item {\n  width: 100%;\n  min-width: 400px;\n  max-width: 500px;\n}\n\n.create-project {\n  margin: 3em auto;\n  max-width: 300px;\n  display: block;\n  cursor: pointer;\n}\n\n.face {\n  text-align: center;\n  margin: auto;\n  display: block;\n  font-size: 5em;\n  margin-bottom: 2rem;\n  margin-top: 2rem;\n  color: #ababab;\n}\n\n.preloader-wrapper {\n  position: absolute;\n  top: 50%;\n  left: 50%;\n}"

/***/ },

/***/ 816:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 817:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 818:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 819:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 820:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 821:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 822:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 823:
/***/ function(module, exports) {

module.exports = ":host >>> .wysiwyg-editor {\n  min-height: 10em;\n}\n\n.actions {\n  padding-top: 2em;\n}"

/***/ },

/***/ 824:
/***/ function(module, exports) {

module.exports = ".card {\n  cursor: pointer;\n}\n\n.card-content .chip {\n  font-size: 10px;\n}\n\n.card-action .material-icons {\n  font-size: 1.4em;\n  margin-top: .35em;\n  margin-right: .3em;\n}\n\n.card-image {\n  max-height: 15em;\n  overflow: hidden;\n}"

/***/ },

/***/ 825:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 826:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 827:
/***/ function(module, exports) {

module.exports = "/* CSS for the font-name + font-size plugin */\n.wysiwyg-plugin-list {\n    max-height: 16em;\n    overflow: auto;\n    overflow-x: hidden;\n    overflow-y: scroll;\n}\n.wysiwyg-plugin-list a,\n.wysiwyg-plugin-list a:link,\n.wysiwyg-plugin-list a:visited {\n    display: block;\n    color: black;\n    padding: 5px 10px;\n    text-decoration: none;\n    cursor: pointer;\n}\n.wysiwyg-plugin-list a:hover {\n    color: HighlightText;\n    background-color: Highlight;\n}\n/* CSS for the smiley plugin */\n.wysiwyg-plugin-smilies {\n    padding: 10px;\n    text-align: center;\n    white-space: normal;\n}\n.wysiwyg-plugin-smilies img {\n    display: -moz-inline-stack; /* inline-block: http://blog.mozilla.org/webdev/2009/02/20/cross-browser-inline-block/ */\n    display: inline-block;\n    *display: inline;\n}\n\n.wysiwyg-browse {\n  height: 50%;\n}\n\n.wysiwyg-editor img {\n    height:auto;\n    max-width: 100%;\n}"

/***/ },

/***/ 830:
/***/ function(module, exports) {

module.exports = "<div class=\"cle-critique\">\n  <nav>\n    <div class=\"nav-wrapper\">\n      <ul id=\"app-component-toolbar\" class=\"nav left\">\n        <li><a href=\"{{basePath}}\"><i class=\"material-icons left\">home</i>Home</a></li>\n      </ul>\n    </div>\n  </nav>\n\n  <div class=\"container\">\n    <router-outlet></router-outlet>\n    <router-outlet name=\"dialog\"></router-outlet>\n  </div>\n</div>"

/***/ },

/***/ 831:
/***/ function(module, exports) {

module.exports = "<div *ngIf=\"assignment\" class=\"assignment\">\n  <i class=\"material-icons assignment__icon\">assignment</i>\n  <h3 class=\"assignment__label\">Assignment Detail</h3>\n  <h4 class=\"assignment__title\">{{ assignment.title }}</h4>\n  <div class=\"assignment__body\" [innerHTML]=\"assignment.body\"></div>\n</div>\n"

/***/ },

/***/ 832:
/***/ function(module, exports) {

module.exports = "<!-- Modal Structure -->\n<div id=\"modal-assignment-dialog\" class=\"modal modal-fixed-footer assignment-dialog\">\n\n  <!--Create or Update Assignment-->\n  <div *ngIf=\"action === 'create' || action === 'update'\">\n    <div class=\"modal-content\">\n      <h2 *ngIf=\"assignment.id\">Edit Assignment</h2>\n      <h2 *ngIf=\"!assignment.id\">Create Assignment</h2>\n      <app-assignment-form [assignment]=\"assignment\" (assignmentSave)=\"onAssignmentSave($event)\"></app-assignment-form>\n    </div>\n    <div class=\"modal-footer\">\n      <a (click)=\"onSave()\" class=\"modal-action modal-close waves-effect waves-green btn-flat\">Save</a>\n      <a (click)=\"onCancel()\" class=\" modal-action modal-close waves-effect waves-green btn-flat\">Cancel</a>\n    </div>\n  </div>\n\n  <!--DELETE Assignment-->\n  <div *ngIf=\"action === 'delete'\">\n    <div class=\"modal-content\">\n      <h2>Are you sure you want to delete this assignment?</h2>\n      <p>The following assignment will be deleted: {{ assignment.title }}</p>\n      <p>Are you sure you want to proceed?</p>\n    </div>\n    <div class=\"modal-footer\">\n      <a (click)=\"onDelete()\" class=\"modal-action modal-close waves-effect waves-red btn-flat\">Delete</a>\n      <a (click)=\"onCancel()\" class=\" modal-action modal-close waves-effect waves-green btn-flat\">Cancel</a>\n    </div>\n  </div>\n</div>\n"

/***/ },

/***/ 833:
/***/ function(module, exports) {

module.exports = "<form [formGroup]=\"form\" class=\"assignment-form\">\n  <input formControlName=\"title\" placeholder=\"Title\" [ngClass]=\"{'invalid': form.controls['title'].status === 'INVALID' && saveAttempted}\">\n  <wysiwygjs formControlName=\"body\"></wysiwygjs>\n\n  <div class=\"submissions-settings fieldset\">\n    <label>Submission settings</label>\n    <div class=\"type\">\n      <label>Type</label>\n      <select formControlName=\"type\">\n        <option *ngFor=\"let type of assignmentOptions.type\" [value]=\"type.value\">{{ type.display }}</option>\n      </select>\n      <div class=\"detail\" *ngIf=\"form.value.type === 'open'\">Students will be able to see all submissions.</div>\n      <div class=\"detail\" *ngIf=\"form.value.type === 'open_after_submission'\">Students will be able to see all submissions AFTER they have made a submission to this assignment.</div>\n      <div class=\"detail\" *ngIf=\"form.value.type === 'closed'\">Students will NOT be able to see each other's submissions.</div>\n    </div>\n\n    <div class=\"late-submissions switch\">\n      <label>\n        No late Submissions\n        <input type=\"checkbox\" formControlName=\"allowLateSubmissions\">\n        <span class=\"lever\"></span>\n        Allow Late Submissions\n      </label>\n    </div>\n  </div>\n\n\n  <div class=\"critique-settings fieldset\" *ngIf=\"assignmentIsCritique\">\n    <label>Critique settings</label>\n    <div class=\"critique-method\">\n      <label>Method</label>\n      <select formControlName=\"critiqueMethod\">\n        <option *ngFor=\"let option of assignmentOptions.critiqueMethod\" [value]=\"option.value\">{{ option.display }}</option>\n      </select>\n    </div>\n\n    <div class=\"critique-subsettings\" *ngIf=\"form.value.critiqueMethod !== 'none'\">\n      <div class=\"critique-privacy switch\">\n        <label>\n          Double-blind\n          <input type=\"checkbox\" formControlName=\"critiquePrivacy\">\n          <span class=\"lever\"></span>\n          Open\n        </label>\n        <div class=\"detail\" *ngIf=\"!form.value.critiquePrivacy\">Submissions will NOT see the author information on submissions or critiques.</div>\n        <div class=\"detail\" *ngIf=\"form.value.critiquePrivacy\">Submissions will see the author information on submissions and critiques.</div>\n      </div>\n    </div>\n  </div>\n\n  <div class=\"due-date\">\n    <div class=\"display\" *ngIf=\"form.value.endDate !==null\">\n      Due date:\n      <span *ngIf=\"form.value.startDate !== null\" class=\"start-date\">\n        {{ form.value.startDate | amDateFormat:'LL hh:mma' }} \n        <span class=\"separator\">\n          to\n        </span>\n      </span>\n      <span class=\"end-date\">\n        {{ form.value.endDate | amDateFormat:'LL hh:mma' }}\n      </span>\n    </div>\n    \n    <div *ngIf=\"form.value.endDate !== null\" class=\"start-date\">\n      <label>Start Date</label>\n      <app-datetime-input formControlName=\"startDate\"></app-datetime-input>\n    </div>\n\n    <div class=\"due-date\">\n      <label>Due Date</label>\n      <app-datetime-input formControlName=\"endDate\"></app-datetime-input>\n    </div>\n  </div>\n</form>"

/***/ },

/***/ 834:
/***/ function(module, exports) {

module.exports = "<div class=\"row\">\n  <ul class=\"collapsible\">\n    <li *ngFor=\"let assignment of assignments\">\n      <div class=\"collapsible-header assignment\" [ngClass]=\"{'assignment--loading': !assignment.id, 'assignment--critique': assignmentService.assignmentIsCritique(assignment)}\">\n        <div class=\"assignment__body\" (click)=\"viewAssignment(assignment.id)\">\n          <i *ngIf=\"!assignmentService.assignmentIsCritique(assignment)\" class=\"material-icons\">assignment</i>\n          <i *ngIf=\"assignmentService.assignmentIsCritique(assignment)\" class=\"material-icons\">arrow_right</i>\n          {{ assignment.title }}\n          <span *ngIf=\"assignment.complete == 1\" class=\"badge green-text\">Complete</span>\n          <span *ngIf=\"assignment.complete == 0\" class=\"badge red-text\">Incomplete</span>\n          <div class=\"due-dates\">\n            <span *ngIf=\"assignment.startDate\">{{ assignment.startDate | amDateFormat:'MM/DD/YY' }} - </span>\n            {{ assignment.endDate | amDateFormat:'MM/DD/YY' }}\n          </div>\n        </div>\n        <div class=\"assignment__icons\">\n          <span *ngIf=\"assignment && assignment.metadata.relatedSubmissions && assignment.metadata.relatedSubmissions.complete.status\" class=\"assignment__icon--complete\"><i class=\"material-icons\">check</i></span>\n        </div>\n        <div class=\"assignment__edit-buttons\" *ngIf=\"assignment.id && (userCanEdit$ | async)\">\n          <a *ngIf=\"!assignmentService.assignmentIsCritique(assignment)\" (click)=\"addCritique(assignment)\"><i class=\"material-icons\" aria-label=\"Edit assignment\">add</i></a>\n          <a (click)=\"onEditAssignment(assignment)\"><i class=\"material-icons\" aria-label=\"Edit assignment\">edit</i></a>\n          <a (click)=\"onDeleteAssignment(assignment)\"><i class=\"material-icons\" aria-label=\"Edit assignment\">delete</i></a>\n        </div>\n        <div class=\"assignment__loading\" *ngIf=\"!assignment.id\">\n          <div class=\"progress\">\n            <div class=\"indeterminate\"></div>\n          </div>\n        </div>\n      </div>\n    </li>\n  </ul>\n</div>"

/***/ },

/***/ 835:
/***/ function(module, exports) {

module.exports = "<div *ngFor=\"let assignment of (assignments$| async)\">\n    <nav>\n      <div class=\"nav-wrapper\">\n        <ul id=\"nav-mobile\" class=\"left\">\n          <li><a routerLink=\"/projects\"><i class=\"material-icons left\">&#xE5C4;</i> projects</a></li>\n        </ul>\n        <ul id=\"nav-mobile\" class=\"right\">\n          <li *ngIf=\"(userCanEdit$ | async)\"><a (click)=\"onEditAssignment(assignment)\" title=\"Edit this assignment\"><i class=\"material-icons left\">edit</i></a></li>\n        </ul>\n      </div>\n    </nav>\n\n    <div class=\"assignment\" *ngIf=\"assignment\">\n      <h1 class=\"assignment__title\">{{ assignment.title }}</h1>\n      <div class=\"assignment__meta\">\n        <div class=\"assignment__dates\">\n          <span *ngIf=\"assignment.startDate\">{{ assignment.startDate | amDateFormat:'LL hh:mmA' }} - </span>\n          {{ assignment.endDate | amDateFormat:'LL hh:mmA' }}\n        </div>\n      </div>\n      <div class=\"assignment__description\" [innerHTML]=\"assignment.body\"> </div>\n    </div>\n\n\n  <app-submission-list *ngIf=\"(submissions$ | async).length > 0\" title=\"Submissions\" [submissions]=\"submissions$ | async\"></app-submission-list>\n\n  <div *ngIf=\"assignment\" class=\"assignment__actions\">\n    <div *ngIf=\"assignment.metadata.submissionActive\">\n      <a *ngIf=\"!assignmentService.assignmentIsCritique(assignment)\" (click)=\"onCreateSubmission(assignment)\" class=\"btn-large\">Submit assignment</a>\n      <a *ngIf=\"assignmentService.assignmentIsCritique(assignment)\" (click)=\"onStartCritique(assignment)\" class=\"btn-large\">Start Critique</a>\n    </div>\n    <div *ngIf=\"!assignment.metadata.submissionActive\" class=\"assignment__rationale\">\n      <p [innerHTML]=\"assignment.metadata.rationale.text\"></p>\n    </div>\n  </div>\n\n  <!--<pre>\n    {{ assignment | json }}\n  </pre>-->\n</div>"

/***/ },

/***/ 836:
/***/ function(module, exports) {

module.exports = "<!-- Dropdown Trigger -->\n<a class='dropdown-button' href='#' data-activates='dropdown1'><i class=\"material-icons text-black\">more_vert</i></a>\n<!-- Dropdown Structure -->\n<ul id='dropdown1' class='dropdown-content'>\n  <li><a href=\"#!\">one</a></li>\n  <li><a href=\"#!\">two</a></li>\n  <li class=\"divider\"></li>\n  <li><a href=\"#!\">three</a></li>\n</ul>"

/***/ },

/***/ 837:
/***/ function(module, exports) {

module.exports = "<wysiwygjs (onFocus)=\"onFocus($event)\" (onChange)=\"onChange($event)\" (onBlur)=\"onBlur($event)\"></wysiwygjs>\n\n\n<button md-raised-button (click)=\"submitForm()\" color=\"primary\">Submit Critique</button>"

/***/ },

/***/ 838:
/***/ function(module, exports) {

module.exports = "critiques list works!"

/***/ },

/***/ 839:
/***/ function(module, exports) {

module.exports = "critique.component"

/***/ },

/***/ 840:
/***/ function(module, exports) {

module.exports = "<p>\n  dashboard works!\n</p>\n"

/***/ },

/***/ 841:
/***/ function(module, exports) {

module.exports = "<div>\n  <input [(ngModel)]=\"day\" (ngModelChange)=\"updateDatetime($event)\" type=\"date\" class=\"datepicker\">\n  <input [(ngModel)]=\"time\" (ngModelChange)=\"updateDatetime($event)\" type=\"time\">\n</div>"

/***/ },

/***/ 842:
/***/ function(module, exports) {

module.exports = "<!-- Modal Structure -->\n<div id=\"modal-dialog\" class=\"modal dialog\">\n\n  <!--Create or Update Assignment-->\n  <div class=\"modal-content\" [innerHTML]=\"content\">\n  </div>\n  <div class=\"modal-footer\">\n    <a (click)=\"onSave()\" class=\"waves-effect waves-green btn-flat\">Save</a>\n    <a (click)=\"onCancel()\" class=\"waves-effect waves-green btn-flat\">Cancel</a>\n  </div>\n</div>\n"

/***/ },

/***/ 843:
/***/ function(module, exports) {

module.exports = "<div *ngIf=\"editing\">\n  <form [formGroup]=\"form\">\n    <input formControlName=\"content\" (keyup.enter)=\"endEditing()\" type=\"text\" class=\"text-input\"> \n  </form>\n</div>\n<div *ngIf=\"editing == false\" (click)=\"beginEditing()\">\n  <ng-content></ng-content>\n</div>\n"

/***/ },

/***/ 844:
/***/ function(module, exports) {

module.exports = "<p>\n  elmsln-wysiwyg works!\n</p>\n"

/***/ },

/***/ 845:
/***/ function(module, exports) {

module.exports = "<p>\n  image works!\n</p>\n"

/***/ },

/***/ 846:
/***/ function(module, exports) {

module.exports = "<form [formGroup]=\"form\" id=\"login-form\" class=\"input-field col s12\">\n  <input formControlName=\"username\" id=\"critique-form-username\" name=\"critique-form-username\" placeholder=\"username\"/>\n  <input formControlName=\"password\" id=\"critique-form-password\" name=\"critique-form-password\" placeholder=\"password\"/>\n</form>\n<button (click)=\"submitForm()\" class=\"btn\" color=\"primary\">Login</button>"

/***/ },

/***/ 847:
/***/ function(module, exports) {

module.exports = "<p>\n  logout works!\n</p>\n"

/***/ },

/***/ 848:
/***/ function(module, exports) {

module.exports = "<p>\n  project-card works!\n</p>\n"

/***/ },

/***/ 849:
/***/ function(module, exports) {

module.exports = "<div class=\"project\">\n  <div class=\"project__header\">\n    <div class=\"project__title-container\">\n\n      <app-editable-field *ngIf=\"(userCanEdit$ | async)\" [type]=\"text\" [content]=\"project.title\" (contentUpdated)=\"updateTitle($event)\">\n        <h1 class=\"project__title\">{{ project.title }}</h1>\n      </app-editable-field>\n      <h1 *ngIf=\"!(userCanEdit$ | async)\" class=\"project__title\">{{ project.title }}</h1>\n\n      <div class=\"project__description\" [innerHTML]=\"project.description\"></div>\n    </div>\n    <div *ngIf=\"(userCanEdit$ | async)\" class=\"project__options\"> \n      <a (click)=\"onCreateAssignment()\" class=\"waves-effect btn-flat tooltipped\" data-tooltip=\"create assignment\"><i class=\"material-icons\">add</i></a>\n      <a (click)=\"onDeleteProject()\" class=\"waves-effect btn-flat tooltipped\" data-tooltip=\"delete assignment\"><i class=\"material-icons\">delete</i></a>\n    </div>\n  </div>\n  <div class=\"project__board\">\n    <cle-assignment-list [assignments]=\"assignments | async\"></cle-assignment-list>\n  </div>\n</div>\n\n<div id=\"modal-{{project.id}}\" class=\"modal delete-project-form\">\n  <div class=\"modal-content\">\n    <h4>Delete project confirmation</h4>\n    <p>Are you sure you want to delete the project titled \"{{ project.title }}\"?</p>\n  </div>\n  <div class=\"modal-footer\">\n    <a (click)=\"confirmDelete(false)\" class=\"modal-action modal-close waves-effect waves-green btn-flat\">Cancel</a>\n    <a (click)=\"confirmDelete(true)\" class=\" modal-action modal-close waves-effect waves-red btn-flat\">Delete</a>\n  </div>\n</div>"

/***/ },

/***/ 850:
/***/ function(module, exports) {

module.exports = "<div *ngIf=\"loading === true\" class=\"preloader-wrapper big active\">\n  <div class=\"spinner-layer spinner-blue-only\">\n    <div class=\"circle-clipper left\">\n      <div class=\"circle\"></div>\n    </div><div class=\"gap-patch\">\n      <div class=\"circle\"></div>\n    </div><div class=\"circle-clipper right\">\n      <div class=\"circle\"></div>\n    </div>\n  </div>\n</div>\n\n<div *ngIf=\"(userCanEdit$ | async)\"> \n  <a (click)=\"createNewProject('Add project')\" class=\"create-project waves-effect waves-light btn-large\"><i class=\"material-icons right\">add</i>New project</a>\n</div>\n\n<div class=\"projects-container\">\n  <app-project-item *ngFor=\"let project of (projects$ | async)\" [project]=\"project\" (delete)=\"projectDeleted(project)\"></app-project-item>\n</div>\n\n"

/***/ },

/***/ 851:
/***/ function(module, exports) {

module.exports = "<p>\n  projects works!\n</p>\n"

/***/ },

/***/ 852:
/***/ function(module, exports) {

module.exports = "<div class=\"submission-create\">\n  <app-submission-form [submission]=\"submission\" (onSubmissionSave)=\"onSubmissionSave($event)\" (onSubmissionCancel)=\"onSubmissionCancel($event)\"></app-submission-form>\n</div>"

/***/ },

/***/ 853:
/***/ function(module, exports) {

module.exports = "<p>\n  submission-critique-form works!\n</p>\n"

/***/ },

/***/ 854:
/***/ function(module, exports) {

module.exports = "<div class=\"submission-detail\" *ngIf=\"submission\">\n  <app-submission-states [submission]=\"submission\"></app-submission-states>\n  <h1>{{ submission.title }}</h1>\n  <div class=\"body\" [innerHTML]=\"submission.body\"></div>\n</div>"

/***/ },

/***/ 855:
/***/ function(module, exports) {

module.exports = "<!-- Modal Structure -->\n<div id=\"modal-submission-dialog\" class=\"modal modal-fixed-footer submission-dialog\">\n  <div class=\"modal-content\">\n  </div>\n  <div class=\"modal-footer\">\n    <a (click)=\"onDelete()\" class=\"modal-action modal-close waves-effect waves-red btn-flat\">Save</a>\n    <a (click)=\"onCancel()\" class=\" modal-action modal-close waves-effect waves-green btn-flat\">Cancel</a>\n  </div>\n</div>"

/***/ },

/***/ 856:
/***/ function(module, exports) {

module.exports = "<app-submission-states [submission]=\"submission\"></app-submission-states>"

/***/ },

/***/ 857:
/***/ function(module, exports) {

module.exports = "<h1>Edit Submission</h1>\n\n<app-assignment-detail \n  [assignment]=\"assignment$ | async\">\n</app-assignment-detail>\n\n<div class=\"submission-edit\">\n  <app-submission-form \n    *ngIf=\"submission$ | async\"\n    [submission]=\"submission$ | async\"\n    (onSubmissionSave)=\"onSubmissionSave($event)\"\n    (onSubmissionCancel)=\"onSubmissionCancel($event)\"\n    (onFormChanges)=\"onFormChanges($event)\">\n  </app-submission-form>\n</div>"

/***/ },

/***/ 858:
/***/ function(module, exports) {

module.exports = "<form *ngIf=\"form\" [formGroup]=\"form\" class=\"submission-form\">\n  <input formControlName=\"title\" placeholder=\"title\" [ngClass]=\"{'invalid': form.controls['title'].status === 'INVALID' && saveAttempted}\">\n  <wysiwygjs \n    formControlName=\"body\"\n    (onWysiwygInit)=\"onWysiwygInit()\"\n    (onImageAdded)=\"onWysiwygImageAdded($event)\"\n    (onImageSave)=\"onImageSave($event)\">\n  </wysiwygjs>\n\n  <div class=\"actions\">\n    <button type=\"submit\" class=\"btn\" (click)=\"submit()\" [ngClass]=\"{'disabled': (savingImage$ | async)}\">Save</button>\n    <a class=\"btn\" (click)=\"cancel()\" [ngClass]=\"{'disabled': (savingImage$ | async)}\">Cancel</a>\n  </div>\n</form>"

/***/ },

/***/ 859:
/***/ function(module, exports) {

module.exports = "<h4 *ngIf=\"title\">{{title}}</h4>\n\n<div class=\"row\">\n  <div *ngFor=\"let submission of submissions\" (click)=\"onSubmissionClick(submission)\" class=\"col s12 m6\">\n   <div class=\"card\">\n    <div class=\"card-image\">\n      <img *ngIf=\"submission.evidence && submission.evidence.images && submission.evidence.images[0] && submission.evidence.images[0].url\" [src]=\"submission.evidence.images[0].url\">\n    </div>\n    <div class=\"card-content\">\n      <h3>{{ submission.title }}</h3>\n    </div>\n    <div class=\"card-action\">\n      <div *ngIf=\"submission.uid === currentUserId\" class=\"chip\"> <span class=\"material-icons left\">person</span> my submission</div>\n      <div *ngIf=\"submission.state === 'submission_in_progress'\" class=\"chip submission-in-progress\"> <span class=\"material-icons left\">autorenew</span> in progress </div>\n      <div *ngIf=\"submission.state === 'submission_ready'\" class=\"chip submission-ready\"> <span class=\"material-icons left\">done</span> complete </div>\n    </div>\n  </div>\n</div>"

/***/ },

/***/ 860:
/***/ function(module, exports) {

module.exports = "<div class=\"submission-states\">\n  <ul *ngIf=\"states\">\n    <li \n      *ngFor=\"let item of states\"\n      [ngClass]=\"{active: item.active, canEdit: submission.metadata.canUpdate}\"\n      [ngStyle]=\"item.styles\"\n      (click)=\"onStateClick(item)\"\n      >\n        <div class=\"submission-item__container\">\n          <i class=\"material-icons left\">{{item.icon}}</i>\n          {{item.display}}\n          </div>\n      </li>\n  </ul>\n</div>\n<app-dialog [content]=\"dialogContent\" (action)=\"onDialogAction($event)\"></app-dialog>\n<!--{{ submission | json }}-->"

/***/ },

/***/ 861:
/***/ function(module, exports) {

module.exports = "<nav>\n  <div class=\"nav-wrapper\">\n    <ul id=\"nav-mobile\" class=\"left\">\n      <li><a (click)=\"onClickBack()\"><i class=\"material-icons left\">&#xE5C4;</i> assignment</a></li>\n    </ul>\n    <ul id=\"nav-mobile-right\" class=\"right\">\n      <li *ngIf=\"userCanEdit$ | async\"><a (click)=\"editSubmission()\"><i class=\"material-icons left\">edit</i></a></li>\n    </ul>\n  </div>\n</nav>\n\n<div *ngIf=\"submissionId\">\n  <app-submission-detail [submission]=\"submission$ | async\"></app-submission-detail>\n</div>"

/***/ },

/***/ 862:
/***/ function(module, exports) {

module.exports = "<p>\n  user works!\n</p>\n"

/***/ },

/***/ 863:
/***/ function(module, exports) {

module.exports = "<textarea>{{ content }}</textarea>"

/***/ },

/***/ 95:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return AppSettings; });
var AppSettings = (function () {
    function AppSettings() {
    }
    Object.defineProperty(AppSettings, "BASE_PATH", {
        get: function () {
            if (typeof Drupal !== 'undefined') {
                return Drupal.settings.basePath;
            }
            else {
                return 'http://studio.elmsln.local/heymp/';
            }
        },
        enumerable: true,
        configurable: true
    });
    return AppSettings;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app-settings.js.map

/***/ },

/***/ 96:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return Submission; });
var Submission = (function () {
    function Submission() {
        this.id = null;
        this.uid = null;
        this.title = null;
        this.status = true;
        this.created = null;
        this.body = null;
        this.assignment = null;
        this.state = 'submission_in_progress';
        this.metadata = {};
        this.environment = {};
        this.evidence = {};
    }
    return Submission;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.js.map

/***/ }

},[1128]);
//# sourceMappingURL=main.bundle.map