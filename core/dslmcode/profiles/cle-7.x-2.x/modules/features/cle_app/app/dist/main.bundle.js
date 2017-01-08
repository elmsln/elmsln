webpackJsonp([0,4],{

/***/ 1096:
/***/ function(module, exports) {

function webpackEmptyContext(req) {
	throw new Error("Cannot find module '" + req + "'.");
}
webpackEmptyContext.keys = function() { return []; };
webpackEmptyContext.resolve = webpackEmptyContext;
module.exports = webpackEmptyContext;
webpackEmptyContext.id = 1096;


/***/ },

/***/ 1097:
/***/ function(module, exports, __webpack_require__) {

module.exports = __webpack_require__(473);


/***/ },

/***/ 117:
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
                return 'http://studio.elmsln.local/studio2/';
            }
        },
        enumerable: true,
        configurable: true
    });
    return AppSettings;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app-settings.js.map

/***/ },

/***/ 118:
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
    LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS'
};
function createProject(project) {
    return {
        type: ActionTypes.CREATE_PROJECT,
        payload: project
    };
}
function createProjectSuccess(projectId) {
    return {
        type: ActionTypes.CREATE_PROJECT_SUCCESS,
        payload: { id: projectId }
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

/***/ 119:
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
var ActionTypes = {
    CREATE_SUBMISSION: 'CREATE_SUBMISSION',
    CREATE_SUBMISSION_SUCCESS: 'CREATE_SUBMISSION_SUCCESS',
    UPDATE_SUBMISSION: 'UPDATE_SUBMISSION',
    UPDATE_SUBMISSION_SUCCESS: 'UPDATE_SUBMISSION_SUCCESS',
    DELETE_SUBMISSION: 'DELETE_SUBMISSION',
    LOAD_SUBMISSIONS: 'LOAD_SUBMISSIONS',
    LOAD_SUBMISSIONS_SUCCESS: 'LOAD_SUBMISSIONS_SUCCESS',
    LOAD_PERMISSIONS: 'LOAD_PERMISSIONS',
    LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS'
};
function createSubmission(submission) {
    return {
        type: ActionTypes.CREATE_SUBMISSION,
        payload: submission
    };
}
function createSubmissionSuccess(submissionId) {
    return {
        type: ActionTypes.CREATE_SUBMISSION_SUCCESS,
        payload: { id: submissionId }
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
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.actions.js.map

/***/ },

/***/ 167:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__elmsln_service__ = __webpack_require__(65);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__app_settings__ = __webpack_require__(117);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__ngrx_store__ = __webpack_require__(13);
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
        return this.elmsln.get(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'node.json?type=cle_project')
            .map(function (data) { return data.json().list; })
            .map(function (data) { return _this.formatProjects(data); });
    };
    ProjectService.prototype.getProject = function (projectId) {
        var _this = this;
        return this.elmsln.get(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'node/' + projectId + '.json')
            .map(function (data) { return data.json(); })
            .map(function (data) { return _this.formatProject(data); });
    };
    ProjectService.prototype.createProject = function (project) {
        // first we need to prepare the object for Drupal
        var body = this.prepareForDrupal(project);
        return this.elmsln.post(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'node', body)
            .map(function (data) { return data.json(); });
    };
    ProjectService.prototype.updateProject = function (project) {
        console.log('updateProject', project);
        // first we need to prepare the object for Drupal
        var body = this.prepareForDrupal(project);
        console.log('updateProject: Ready to send', body);
        return this.elmsln.put(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'node/' + project.id, body)
            .map(function (data) { return data.json(); });
    };
    ProjectService.prototype.deleteProject = function (project) {
        return this.elmsln.delete(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'node/' + project.id)
            .map(function (data) { return data.json(); });
    };
    ProjectService.prototype.formatProjects = function (projects) {
        var _this = this;
        var newProjects = [];
        projects.forEach(function (project) {
            newProjects.push(_this.formatProject(project));
        });
        return newProjects;
    };
    ProjectService.prototype.formatProject = function (project) {
        var newProject = {
            title: project.title ? project.title : null,
            id: project.nid ? Number(project.nid) : null
        };
        // Convert date fields
        var dateFields = ['startDate', 'endDate'];
        dateFields.forEach(function (field) {
            if (newProject[field]) {
                newProject[field] = new Date(newProject[field] * 1000);
            }
        });
        return newProject;
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
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__elmsln_service__["a" /* ElmslnService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], ProjectService);
    return ProjectService;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project.service.js.map

/***/ },

/***/ 168:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return Submission; });
var Submission = (function () {
    function Submission() {
        this.id = null;
        this.title = null;
        this.status = null;
        this.created = null;
        this.body = null;
        this.assignment = null;
        this.metadata = {};
        this.state = null;
    }
    return Submission;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.js.map

/***/ },

/***/ 248:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__user_service__ = __webpack_require__(252);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__ngrx_store__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__app_actions__ = __webpack_require__(92);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__submission_submission_actions__ = __webpack_require__(119);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__projects_project_actions__ = __webpack_require__(118);
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
            template: __webpack_require__(806),
            styles: [__webpack_require__(778)],
            providers: [__WEBPACK_IMPORTED_MODULE_1__user_service__["a" /* UserService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], AppComponent);
    return AppComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.component.js.map

/***/ },

/***/ 249:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "a", function() { return Assignment; });
var Assignment = (function () {
    function Assignment() {
        this.id = null;
        this.title = null;
        this.type = null;
        this.status = true;
        this.created = null;
        this.startDate = null;
        this.endDate = null;
        this.project = null;
        this.body = null;
        this.critiqueMethod = null;
        this.critiquePrivacy = null;
        this.critiqueStyle = null;
        this.metadata = {};
    }
    return Assignment;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment.js.map

/***/ },

/***/ 250:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_http__ = __webpack_require__(233);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__app_settings__ = __webpack_require__(117);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__elmsln_service__ = __webpack_require__(65);
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

/***/ 251:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(76);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__submission__ = __webpack_require__(168);
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
    function SubmissionFormComponent(formBuilder) {
        this.formBuilder = formBuilder;
        this.onSubmissionSave = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.onSubmissionCancel = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.onFormChanges = new __WEBPACK_IMPORTED_MODULE_0__angular_core__["EventEmitter"]();
        this.formValueChanges = 0;
    }
    SubmissionFormComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.form = this.formBuilder.group(this.submission);
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
    };
    SubmissionFormComponent.prototype.ngOnChanges = function () {
        this.form = this.formBuilder.group(this.submission);
    };
    SubmissionFormComponent.prototype.onWysiwygInit = function () {
        this.form.markAsPristine();
    };
    SubmissionFormComponent.prototype.submit = function () {
        var model = this.form.value;
        this.onSubmissionSave.emit(model);
    };
    SubmissionFormComponent.prototype.cancel = function () {
        this.onSubmissionCancel.emit();
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__submission__["a" /* Submission */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__submission__["a" /* Submission */]) === 'function' && _a) || Object)
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
            template: __webpack_require__(827),
            styles: [__webpack_require__(799)]
        }), 
        __metadata('design:paramtypes', [(typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */]) === 'function' && _e) || Object])
    ], SubmissionFormComponent);
    return SubmissionFormComponent;
    var _a, _b, _c, _d, _e;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-form.component.js.map

/***/ },

/***/ 252:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__elmsln_service__ = __webpack_require__(65);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ng2_cookies_ng2_cookies__ = __webpack_require__(441);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_ng2_cookies_ng2_cookies___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_ng2_cookies_ng2_cookies__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__app_actions__ = __webpack_require__(92);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(13);
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
    UserService = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__elmsln_service__["a" /* ElmslnService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], UserService);
    return UserService;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/user.service.js.map

/***/ },

/***/ 387:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__assignment__ = __webpack_require__(249);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__assignment_service__ = __webpack_require__(64);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__assignment_form_assignment_form_component__ = __webpack_require__(388);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__ngrx_store__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__app_actions__ = __webpack_require__(92);
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
                    .subscribe(function (data) {
                    _this.assignment = data;
                });
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
            this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__app_actions__["c" /* updateAssignment */])($event));
        }
        else {
            this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__app_actions__["d" /* createAssignment */])($event));
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
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_6__app_actions__["e" /* deleteAssignment */])(this.assignment));
        this.router.navigate([{ outlets: { dialog: null } }]);
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["ViewChild"])(__WEBPACK_IMPORTED_MODULE_4__assignment_form_assignment_form_component__["a" /* AssignmentFormComponent */]), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_4__assignment_form_assignment_form_component__["a" /* AssignmentFormComponent */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__assignment_form_assignment_form_component__["a" /* AssignmentFormComponent */]) === 'function' && _a) || Object)
    ], AssignmentDialogComponent.prototype, "assignmentFormComponent", void 0);
    AssignmentDialogComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-assignment-dialog',
            template: __webpack_require__(807),
            styles: [__webpack_require__(779)],
            providers: [__WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _e) || Object, (typeof (_f = typeof __WEBPACK_IMPORTED_MODULE_5__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_5__ngrx_store__["a" /* Store */]) === 'function' && _f) || Object])
    ], AssignmentDialogComponent);
    return AssignmentDialogComponent;
    var _a, _b, _c, _d, _e, _f;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment-dialog.component.js.map

/***/ },

/***/ 388:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(76);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__assignment__ = __webpack_require__(249);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__assignment_service__ = __webpack_require__(64);
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
        // create the form from the assignment object that we recieved
        this.form = this.formBuilder.group(this.assignment);
        // get a list of assignment 'types' that we have available so we can display
        // those in the select field
        this.assignmentOptions = this.assignmentService.getAssignmentOptions();
    };
    AssignmentFormComponent.prototype.ngOnChanges = function () {
        var _this = this;
        this.form = this.formBuilder.group(this.assignment);
        this.form.valueChanges
            .debounceTime(1000)
            .subscribe(function () { return _this.autoSaveForm(); });
    };
    AssignmentFormComponent.prototype.autoSaveForm = function () {
        var saved = localStorage.getItem('assignments_autosave') ? JSON.parse(localStorage.getItem('assignments_autosave')) : [];
        var currentForm = this.form.value;
        var newSaved;
        if (currentForm.id) {
            saved.map(function (assignment) {
                if (assignment.id === currentForm.id) {
                    return currentForm;
                }
                return assignment;
            });
        }
        else {
            newSaved['new_assignment'] = currentForm;
        }
        localStorage.setItem('assignments_autosave', JSON.stringify(newSaved));
    };
    AssignmentFormComponent.prototype.save = function () {
        var model = this.form.value;
        this.assignmentSave.emit(model);
        this.form.reset();
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
            template: __webpack_require__(808),
            styles: [__webpack_require__(780)],
            providers: [__WEBPACK_IMPORTED_MODULE_3__assignment__["a" /* Assignment */], __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */]) === 'function' && _e) || Object])
    ], AssignmentFormComponent);
    return AssignmentFormComponent;
    var _a, _b, _c, _d, _e;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment-form.component.js.map

/***/ },

/***/ 389:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_common__ = __webpack_require__(72);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__assignment_service__ = __webpack_require__(64);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(13);
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
    function AssignmentComponent(router, route, location, assignmentService, el, store) {
        this.router = router;
        this.route = route;
        this.location = location;
        this.assignmentService = assignmentService;
        this.el = el;
        this.store = store;
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
        // get the submissions
        this.submissions$ = this.store.select('submissions')
            .map(function (state) {
            return state.submissions.filter(function (sub) { return sub.assignment === _this.assignmentId; });
        });
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
    AssignmentComponent.prototype.onEditAssignment = function (assignment) {
        var url = 'assignment-edit/' + assignment.id;
        this.router.navigate([{ outlets: { dialog: url } }]);
    };
    AssignmentComponent.prototype.onCreateSubmission = function (assignment) {
        var url = 'submissions/create/' + assignment.id;
        this.router.navigate([url]);
    };
    AssignmentComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'cle-assignment',
            template: __webpack_require__(810),
            styles: [__webpack_require__(782)],
            providers: [__WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__assignment_service__["a" /* AssignmentService */]) === 'function' && _d) || Object, (typeof (_e = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _e) || Object, (typeof (_f = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _f) || Object])
    ], AssignmentComponent);
    return AssignmentComponent;
    var _a, _b, _c, _d, _e, _f;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment.component.js.map

/***/ },

/***/ 390:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(76);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__user_service__ = __webpack_require__(252);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(13);
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
            template: __webpack_require__(818),
            styles: [__webpack_require__(790)],
            providers: [__WEBPACK_IMPORTED_MODULE_2__user_service__["a" /* UserService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__user_service__["a" /* UserService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__user_service__["a" /* UserService */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_3__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _d) || Object])
    ], LoginComponent);
    return LoginComponent;
    var _a, _b, _c, _d;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/login.component.js.map

/***/ },

/***/ 391:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__user_service__ = __webpack_require__(252);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_router__ = __webpack_require__(24);
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
            template: __webpack_require__(819),
            styles: [__webpack_require__(791)],
            providers: [__WEBPACK_IMPORTED_MODULE_1__user_service__["a" /* UserService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__user_service__["a" /* UserService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__user_service__["a" /* UserService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_router__["a" /* Router */]) === 'function' && _b) || Object])
    ], LogoutComponent);
    return LogoutComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/logout.component.js.map

/***/ },

/***/ 392:
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

/***/ 393:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__project__ = __webpack_require__(392);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__project_service__ = __webpack_require__(167);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__project_actions__ = __webpack_require__(118);
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
            template: __webpack_require__(822),
            styles: [__webpack_require__(794)],
            providers: [__WEBPACK_IMPORTED_MODULE_2__project_service__["a" /* ProjectService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__project_service__["a" /* ProjectService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__project_service__["a" /* ProjectService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_3__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__angular_router__["a" /* Router */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__ngrx_store__["a" /* Store */]) === 'function' && _c) || Object])
    ], ProjectsListComponent);
    return ProjectsListComponent;
    var _a, _b, _c;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/projects-list.component.js.map

/***/ },

/***/ 394:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_store__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__submission__ = __webpack_require__(168);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__submission_actions__ = __webpack_require__(119);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__submission_form_submission_form_component__ = __webpack_require__(251);
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
    };
    SubmissionCreateComponent.prototype.onSubmissionSave = function ($event) {
        var assignmentId = this.assignmentId;
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_4__submission_actions__["b" /* createSubmission */])($event));
        this.router.navigate(['/assignments/' + assignmentId]);
        this.submissionFormComponent.form.reset();
    };
    SubmissionCreateComponent.prototype.onSubmissionCancel = function ($event) {
        var assignmentId = this.assignmentId;
        this.router.navigate(['/assignments/' + assignmentId]);
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["ViewChild"])(__WEBPACK_IMPORTED_MODULE_5__submission_form_submission_form_component__["a" /* SubmissionFormComponent */]), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_5__submission_form_submission_form_component__["a" /* SubmissionFormComponent */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_5__submission_form_submission_form_component__["a" /* SubmissionFormComponent */]) === 'function' && _a) || Object)
    ], SubmissionCreateComponent.prototype, "submissionFormComponent", void 0);
    SubmissionCreateComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-create',
            template: __webpack_require__(824),
            styles: [__webpack_require__(796)]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */]) === 'function' && _d) || Object])
    ], SubmissionCreateComponent);
    return SubmissionCreateComponent;
    var _a, _b, _c, _d;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-create.component.js.map

/***/ },

/***/ 395:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_store__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__submission_actions__ = __webpack_require__(119);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__submission_form_submission_form_component__ = __webpack_require__(251);
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
    function SubmissionEditComponent(route, router, store) {
        this.route = route;
        this.router = router;
        this.store = store;
    }
    SubmissionEditComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params.forEach(function (params) {
            if (typeof params['submissionId'] !== 'undefined') {
                var id = params['submissionId'];
                _this.submissionId = Number(id);
                console.log(_this.submissionId);
            }
        });
        if (this.submissionId) {
            this.submission$ = this.store.select('submissions')
                .map(function (state) { return state.submissions.find(function (sub) { return sub.id === _this.submissionId; }); });
        }
    };
    SubmissionEditComponent.prototype.onSubmissionSave = function ($event) {
        this.store.dispatch(__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["c" /* updateSubmission */])($event));
        this.submissionFormComponent.form.reset();
        this.router.navigate(['/submissions/' + this.submissionId]);
    };
    SubmissionEditComponent.prototype.onSubmissionCancel = function () {
        if (this.submissionFormDirty) {
            if (confirm('You have unsaved changes. Are you sure you want to navigate away from this page?')) {
                this.router.navigate(['/submissions/' + this.submissionId]);
                this.submissionFormComponent.form.reset();
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
            template: __webpack_require__(826),
            styles: [__webpack_require__(798)]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_store__["a" /* Store */]) === 'function' && _d) || Object])
    ], SubmissionEditComponent);
    return SubmissionEditComponent;
    var _a, _b, _c, _d;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-edit.component.js.map

/***/ },

/***/ 396:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_common__ = __webpack_require__(72);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__ngrx_store__ = __webpack_require__(13);
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
    function SubmissionComponent(route, store, router, location) {
        this.route = route;
        this.store = store;
        this.router = router;
        this.location = location;
    }
    SubmissionComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.route.params
            .subscribe(function (params) {
            if (params['submissionId']) {
                _this.submissionId = Number(params['submissionId']);
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
            template: __webpack_require__(829),
            styles: [__webpack_require__(801)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_3__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */]) === 'function' && _d) || Object])
    ], SubmissionComponent);
    return SubmissionComponent;
    var _a, _b, _c, _d;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.component.js.map

/***/ },

/***/ 397:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngrx_store__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__elmsln_service__ = __webpack_require__(65);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__app_settings__ = __webpack_require__(117);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__submission__ = __webpack_require__(168);
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
            .map(function (data) { return data.json().data; })
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
            .map(function (data) { return data.json().data; })
            .map(function (data) { return _this.convertToSubmission(data); });
    };
    SubmissionService.prototype.createSubmission = function (submission) {
        var newSub = this.prepareForDrupal(submission);
        return this.elmsln.post(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'node', newSub)
            .map(function (data) { return data.json(); });
    };
    SubmissionService.prototype.updateSubmission = function (submission) {
        var newSub = this.prepareForDrupal(submission);
        return this.elmsln.put(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'node/' + submission.id, newSub)
            .map(function (data) { return data.json(); });
    };
    SubmissionService.prototype.deleteSubmission = function (submission) {
        return this.elmsln.delete(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'node/' + submission.id)
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
        if (typeof data.evidence.body !== 'undefined') {
            converted.body = data.evidence.body;
        }
        return converted;
    };
    SubmissionService.prototype.prepareForDrupal = function (submission) {
        var newSub = {};
        newSub.type = 'cle_submission';
        if (submission.title) {
            newSub.title = submission.title;
        }
        if (submission.body) {
            newSub.field_submission_text = {
                value: submission.body,
                format: 'student_format'
            };
        }
        if (submission.assignment) {
            newSub.field_assignment = submission.assignment;
        }
        return newSub;
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

/***/ 472:
/***/ function(module, exports) {

function webpackEmptyContext(req) {
	throw new Error("Cannot find module '" + req + "'.");
}
webpackEmptyContext.keys = function() { return []; };
webpackEmptyContext.resolve = webpackEmptyContext;
module.exports = webpackEmptyContext;
webpackEmptyContext.id = 472;


/***/ },

/***/ 473:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__polyfills_ts__ = __webpack_require__(620);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__polyfills_ts___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0__polyfills_ts__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_platform_browser_dynamic__ = __webpack_require__(555);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__environments_environment__ = __webpack_require__(619);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__app___ = __webpack_require__(605);





if (__WEBPACK_IMPORTED_MODULE_3__environments_environment__["a" /* environment */].production) {
    __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__angular_core__["enableProdMode"])();
}
__webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1__angular_platform_browser_dynamic__["a" /* platformBrowserDynamic */])().bootstrapModule(__WEBPACK_IMPORTED_MODULE_4__app___["a" /* AppModule */]);
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/main.js.map

/***/ },

/***/ 593:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__ = __webpack_require__(179);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__ = __webpack_require__(166);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__app_actions__ = __webpack_require__(92);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__assignment_service__ = __webpack_require__(64);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__elmsln_service__ = __webpack_require__(65);
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
            .ofType(__WEBPACK_IMPORTED_MODULE_3__app_actions__["f" /* ActionTypes */].CREATE_ASSIGNMENT)
            .mergeMap(function (action) { return _this.assignmentService.createAssignment(action.payload); })
            .map(function (assignmentId) {
            Materialize.toast('Assignment created', 1500);
            return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__app_actions__["g" /* createAssignmentSuccess */])(assignmentId);
        });
        // Update the assignment on the server
        this.updateAssignment$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__app_actions__["f" /* ActionTypes */].UPDATE_ASSIGNMENT)
            .map(function (state) {
            Materialize.toast('Assignment updating...', 1500);
            return state;
        })
            .mergeMap(function (action) {
            return _this.assignmentService.updateAssignment(action.payload)
                .mergeMap(function (data) { return _this.assignmentService.getAssignment(action.payload.id); });
        })
            .map(function (assignment) {
            Materialize.toast('Assignment updated', 1500);
            return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__app_actions__["h" /* updateAssignmentSuccess */])(assignment);
        });
        this.loadAssignments$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__app_actions__["f" /* ActionTypes */].LOAD_ASSIGNMENTS)
            .mergeMap(function () { return _this.assignmentService.loadAssignments(); })
            .map(function (assignments) { return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__app_actions__["i" /* loadAssignmentsSuccess */])(assignments); });
        // Populate the user.permissions store when the user profile returns
        this.loadPermissions$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__app_actions__["f" /* ActionTypes */].LOAD_PERMISSIONS)
            .mergeMap(function () { return _this.elmslnService.getUserProfile(); })
            .map(function (profile) {
            if (typeof profile.user.permissions !== 'undefined') {
                return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__app_actions__["j" /* loadPermissionsSuccess */])(profile.user.permissions, profile.user['csrf-token']);
            }
            else {
                return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__app_actions__["j" /* loadPermissionsSuccess */])([], null);
            }
        });
        this.deleteAssignment$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__app_actions__["f" /* ActionTypes */].DELETE_ASSIGNMENT)
            .mergeMap(function (action) { return _this.assignmentService.deleteAssignment(action.payload); })
            .map(function (info) {
            Materialize.toast('Assignment deleted', 1000);
        });
    }
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "createAssignment$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "updateAssignment$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "loadAssignments$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])(), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "loadPermissions$", void 0);
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["a" /* Effect */])({ dispatch: false }), 
        __metadata('design:type', Object)
    ], AppEffects.prototype, "deleteAssignment$", void 0);
    AppEffects = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["b" /* Actions */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["b" /* Actions */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__assignment_service__["a" /* AssignmentService */]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_5__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_5__elmsln_service__["a" /* ElmslnService */]) === 'function' && _c) || Object])
    ], AppEffects);
    return AppEffects;
    var _a, _b, _c;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.effects.js.map

/***/ },

/***/ 594:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_platform_browser__ = __webpack_require__(163);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_forms__ = __webpack_require__(76);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__angular_http__ = __webpack_require__(233);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__app_routing__ = __webpack_require__(595);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__ngrx_store__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__ngrx_store_devtools__ = __webpack_require__(589);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7__ngrx_effects__ = __webpack_require__(166);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8__reducers_assignments__ = __webpack_require__(611);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9__reducers_users__ = __webpack_require__(612);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10__submission_submission_reducer__ = __webpack_require__(616);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11__projects_project_reducer__ = __webpack_require__(609);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12__app_effects__ = __webpack_require__(593);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_13__submission_submission_effects__ = __webpack_require__(615);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_14__projects_project_effects__ = __webpack_require__(608);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_15__elmsln_service__ = __webpack_require__(65);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_16__critique_service__ = __webpack_require__(250);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_17__assignment_service__ = __webpack_require__(64);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_18__submission_submission_service__ = __webpack_require__(397);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_19__project_service__ = __webpack_require__(167);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_20_angular2_moment__ = __webpack_require__(621);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_20_angular2_moment___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_20_angular2_moment__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_21__app_component__ = __webpack_require__(248);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_22__assignment_assignment_component__ = __webpack_require__(389);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_23__assignment_assignment_list_assignment_list_component__ = __webpack_require__(596);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_24__dashboard_dashboard_component__ = __webpack_require__(602);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_25__user_user_component__ = __webpack_require__(617);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_26__critique_critique_component__ = __webpack_require__(601);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_27__critique_critique_form_critique_form_component__ = __webpack_require__(599);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_28__login_login_component__ = __webpack_require__(390);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_29__logout_logout_component__ = __webpack_require__(391);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_30__critique_critique_list_critique_list_component__ = __webpack_require__(600);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_31__wysiwygjs_wysiwygjs_component__ = __webpack_require__(618);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_32__assignment_assignment_form_assignment_form_component__ = __webpack_require__(388);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_33__projects_projects_component__ = __webpack_require__(610);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_34__projects_projects_list_projects_list_component__ = __webpack_require__(393);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_35__components_dropdown_dropdown_component__ = __webpack_require__(597);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_36__projects_project_card_project_card_component__ = __webpack_require__(606);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_37__projects_project_item_project_item_component__ = __webpack_require__(607);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_38__editable_field_editable_field_component__ = __webpack_require__(604);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_39__datetime_input_datetime_input_component__ = __webpack_require__(603);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_40__assignment_assignment_dialog_assignment_dialog_component__ = __webpack_require__(387);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_41__submission_submission_create_submission_create_component__ = __webpack_require__(394);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_42__submission_submission_form_submission_form_component__ = __webpack_require__(251);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_43__submission_submission_list_submission_list_component__ = __webpack_require__(614);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_44__submission_submission_detail_submission_detail_component__ = __webpack_require__(613);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_45__submission_submission_component__ = __webpack_require__(396);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_46__submission_submission_edit_submission_edit_component__ = __webpack_require__(395);
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
                __WEBPACK_IMPORTED_MODULE_21__app_component__["a" /* AppComponent */],
                __WEBPACK_IMPORTED_MODULE_22__assignment_assignment_component__["a" /* AssignmentComponent */],
                __WEBPACK_IMPORTED_MODULE_23__assignment_assignment_list_assignment_list_component__["a" /* AssignmentListComponent */],
                __WEBPACK_IMPORTED_MODULE_24__dashboard_dashboard_component__["a" /* DashboardComponent */],
                __WEBPACK_IMPORTED_MODULE_25__user_user_component__["a" /* UserComponent */],
                __WEBPACK_IMPORTED_MODULE_26__critique_critique_component__["a" /* CritiqueComponent */],
                __WEBPACK_IMPORTED_MODULE_27__critique_critique_form_critique_form_component__["a" /* CritiqueFormComponent */],
                __WEBPACK_IMPORTED_MODULE_28__login_login_component__["a" /* LoginComponent */],
                __WEBPACK_IMPORTED_MODULE_29__logout_logout_component__["a" /* LogoutComponent */],
                __WEBPACK_IMPORTED_MODULE_30__critique_critique_list_critique_list_component__["a" /* CritiqueListComponent */],
                __WEBPACK_IMPORTED_MODULE_31__wysiwygjs_wysiwygjs_component__["a" /* WysiwygjsComponent */],
                __WEBPACK_IMPORTED_MODULE_32__assignment_assignment_form_assignment_form_component__["a" /* AssignmentFormComponent */],
                __WEBPACK_IMPORTED_MODULE_33__projects_projects_component__["a" /* ProjectsComponent */],
                __WEBPACK_IMPORTED_MODULE_34__projects_projects_list_projects_list_component__["a" /* ProjectsListComponent */],
                __WEBPACK_IMPORTED_MODULE_35__components_dropdown_dropdown_component__["a" /* DropdownComponent */],
                __WEBPACK_IMPORTED_MODULE_36__projects_project_card_project_card_component__["a" /* ProjectCardComponent */],
                __WEBPACK_IMPORTED_MODULE_37__projects_project_item_project_item_component__["a" /* ProjectItemComponent */],
                __WEBPACK_IMPORTED_MODULE_38__editable_field_editable_field_component__["a" /* EditableFieldComponent */],
                __WEBPACK_IMPORTED_MODULE_39__datetime_input_datetime_input_component__["a" /* DatetimeInputComponent */],
                __WEBPACK_IMPORTED_MODULE_40__assignment_assignment_dialog_assignment_dialog_component__["a" /* AssignmentDialogComponent */],
                __WEBPACK_IMPORTED_MODULE_45__submission_submission_component__["a" /* SubmissionComponent */],
                __WEBPACK_IMPORTED_MODULE_41__submission_submission_create_submission_create_component__["a" /* SubmissionCreateComponent */],
                __WEBPACK_IMPORTED_MODULE_42__submission_submission_form_submission_form_component__["a" /* SubmissionFormComponent */],
                __WEBPACK_IMPORTED_MODULE_43__submission_submission_list_submission_list_component__["a" /* SubmissionListComponent */],
                __WEBPACK_IMPORTED_MODULE_44__submission_submission_detail_submission_detail_component__["a" /* SubmissionDetailComponent */],
                __WEBPACK_IMPORTED_MODULE_46__submission_submission_edit_submission_edit_component__["a" /* SubmissionEditComponent */]
            ],
            imports: [
                __WEBPACK_IMPORTED_MODULE_0__angular_platform_browser__["b" /* BrowserModule */],
                __WEBPACK_IMPORTED_MODULE_3__angular_http__["c" /* HttpModule */],
                __WEBPACK_IMPORTED_MODULE_4__app_routing__["a" /* routing */],
                __WEBPACK_IMPORTED_MODULE_2__angular_forms__["c" /* FormsModule */],
                __WEBPACK_IMPORTED_MODULE_2__angular_forms__["d" /* ReactiveFormsModule */],
                __WEBPACK_IMPORTED_MODULE_20_angular2_moment__["MomentModule"],
                __WEBPACK_IMPORTED_MODULE_5__ngrx_store__["g" /* StoreModule */].provideStore({
                    assignments: __WEBPACK_IMPORTED_MODULE_8__reducers_assignments__["a" /* reducer */],
                    user: __WEBPACK_IMPORTED_MODULE_9__reducers_users__["a" /* reducer */],
                    submissions: __WEBPACK_IMPORTED_MODULE_10__submission_submission_reducer__["a" /* submissionReducer */],
                    projects: __WEBPACK_IMPORTED_MODULE_11__projects_project_reducer__["a" /* projectReducer */]
                }),
                __WEBPACK_IMPORTED_MODULE_7__ngrx_effects__["c" /* EffectsModule */].run(__WEBPACK_IMPORTED_MODULE_12__app_effects__["a" /* AppEffects */]),
                __WEBPACK_IMPORTED_MODULE_7__ngrx_effects__["c" /* EffectsModule */].run(__WEBPACK_IMPORTED_MODULE_13__submission_submission_effects__["a" /* SubmissionEffects */]),
                __WEBPACK_IMPORTED_MODULE_7__ngrx_effects__["c" /* EffectsModule */].run(__WEBPACK_IMPORTED_MODULE_14__projects_project_effects__["a" /* ProjectEffects */]),
                __WEBPACK_IMPORTED_MODULE_6__ngrx_store_devtools__["a" /* StoreDevtoolsModule */].instrumentOnlyWithExtension()
            ],
            providers: [
                __WEBPACK_IMPORTED_MODULE_15__elmsln_service__["a" /* ElmslnService */],
                __WEBPACK_IMPORTED_MODULE_16__critique_service__["a" /* CritiqueService */],
                __WEBPACK_IMPORTED_MODULE_17__assignment_service__["a" /* AssignmentService */],
                __WEBPACK_IMPORTED_MODULE_18__submission_submission_service__["a" /* SubmissionService */],
                __WEBPACK_IMPORTED_MODULE_19__project_service__["a" /* ProjectService */]
            ],
            bootstrap: [__WEBPACK_IMPORTED_MODULE_21__app_component__["a" /* AppComponent */]]
        }), 
        __metadata('design:paramtypes', [])
    ], AppModule);
    return AppModule;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.module.js.map

/***/ },

/***/ 595:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__app_component__ = __webpack_require__(248);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__assignment_assignment_component__ = __webpack_require__(389);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__login_login_component__ = __webpack_require__(390);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__logout_logout_component__ = __webpack_require__(391);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__projects_projects_list_projects_list_component__ = __webpack_require__(393);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__assignment_assignment_dialog_assignment_dialog_component__ = __webpack_require__(387);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7__submission_submission_component__ = __webpack_require__(396);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8__submission_submission_create_submission_create_component__ = __webpack_require__(394);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9__submission_submission_edit_submission_edit_component__ = __webpack_require__(395);
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
            }
        ]
    }
];
var appRoutingProviders = [];
var routing = __WEBPACK_IMPORTED_MODULE_0__angular_router__["c" /* RouterModule */].forRoot(appRoutes);
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.routing.js.map

/***/ },

/***/ 596:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__assignment_service__ = __webpack_require__(64);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__ngrx_store__ = __webpack_require__(13);
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
            template: __webpack_require__(809),
            styles: [__webpack_require__(781)],
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

/***/ 597:
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
            template: __webpack_require__(811),
            styles: [__webpack_require__(783)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _a) || Object])
    ], DropdownComponent);
    return DropdownComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/dropdown.component.js.map

/***/ },

/***/ 598:
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

/***/ 599:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__critique__ = __webpack_require__(598);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__critique_service__ = __webpack_require__(250);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_rxjs_Rx__ = __webpack_require__(834);
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
            template: __webpack_require__(812),
            styles: [__webpack_require__(784)],
            providers: [__WEBPACK_IMPORTED_MODULE_2__critique_service__["a" /* CritiqueService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__critique_service__["a" /* CritiqueService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__critique_service__["a" /* CritiqueService */]) === 'function' && _b) || Object])
    ], CritiqueFormComponent);
    return CritiqueFormComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/critique-form.component.js.map

/***/ },

/***/ 600:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__critique_service__ = __webpack_require__(250);
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
            template: __webpack_require__(813),
            styles: [__webpack_require__(785)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__critique_service__["a" /* CritiqueService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__critique_service__["a" /* CritiqueService */]) === 'function' && _a) || Object])
    ], CritiqueListComponent);
    return CritiqueListComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/critique-list.component.js.map

/***/ },

/***/ 601:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_common__ = __webpack_require__(72);
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
            template: __webpack_require__(814),
            styles: [__webpack_require__(786)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["b" /* ActivatedRoute */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__angular_common__["f" /* Location */]) === 'function' && _b) || Object])
    ], CritiqueComponent);
    return CritiqueComponent;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/critique.component.js.map

/***/ },

/***/ 602:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__assignment_service__ = __webpack_require__(64);
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
            template: __webpack_require__(815),
            styles: [__webpack_require__(787)],
            providers: [__WEBPACK_IMPORTED_MODULE_1__assignment_service__["a" /* AssignmentService */]]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__assignment_service__["a" /* AssignmentService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__assignment_service__["a" /* AssignmentService */]) === 'function' && _a) || Object])
    ], DashboardComponent);
    return DashboardComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/dashboard.component.js.map

/***/ },

/***/ 603:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(76);
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
            template: __webpack_require__(816),
            styles: [__webpack_require__(788)],
            providers: [
                {
                    provide: __WEBPACK_IMPORTED_MODULE_1__angular_forms__["b" /* NG_VALUE_ACCESSOR */],
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

/***/ 604:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(76);
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
            template: __webpack_require__(817),
            styles: [__webpack_require__(789)]
        }), 
        __metadata('design:paramtypes', [(typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _b) || Object, (typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_forms__["a" /* FormBuilder */]) === 'function' && _c) || Object])
    ], EditableFieldComponent);
    return EditableFieldComponent;
    var _a, _b, _c;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/editable-field.component.js.map

/***/ },

/***/ 605:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__app_component__ = __webpack_require__(248);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__app_module__ = __webpack_require__(594);
/* unused harmony namespace reexport */
/* harmony namespace reexport (by used) */ __webpack_require__.d(exports, "a", function() { return __WEBPACK_IMPORTED_MODULE_1__app_module__["a"]; });


//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/index.js.map

/***/ },

/***/ 606:
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
            template: __webpack_require__(820),
            styles: [__webpack_require__(792)]
        }), 
        __metadata('design:paramtypes', [])
    ], ProjectCardComponent);
    return ProjectCardComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project-card.component.js.map

/***/ },

/***/ 607:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(24);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__project__ = __webpack_require__(392);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__project_service__ = __webpack_require__(167);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__assignment_service__ = __webpack_require__(64);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__ngrx_store__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__project_actions__ = __webpack_require__(118);
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
            template: __webpack_require__(821),
            styles: [__webpack_require__(793)],
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

/***/ 608:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__ = __webpack_require__(179);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__ = __webpack_require__(166);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__project_actions__ = __webpack_require__(118);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__project_service__ = __webpack_require__(167);
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
            .map(function (projectInfo) {
            Materialize.toast('Project created', 1500);
            return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__project_actions__["d" /* createProjectSuccess */])(projectInfo.id);
        });
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
            Materialize.toast('Project deleted', 1000);
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

/***/ 609:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__project_actions__ = __webpack_require__(118);
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
            var projectId_1 = action.payload.id ? Number(action.payload.id) : null;
            return {
                projects: state.projects.map(function (project) {
                    if (!project.id && projectId_1) {
                        return Object.assign({}, project, { id: projectId_1 });
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
            console.log(state.projects, action.payload);
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
        default: {
            return state;
        }
    }
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/project.reducer.js.map

/***/ },

/***/ 610:
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
            template: __webpack_require__(823),
            styles: [__webpack_require__(795)]
        }), 
        __metadata('design:paramtypes', [])
    ], ProjectsComponent);
    return ProjectsComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/projects.component.js.map

/***/ },

/***/ 611:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__app_actions__ = __webpack_require__(92);
/* harmony export (immutable) */ exports["a"] = reducer;

var initialState = {
    loading: false,
    assignments: []
};
function reducer(state, action) {
    if (state === void 0) { state = initialState; }
    switch (action.type) {
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["f" /* ActionTypes */].CREATE_ASSIGNMENT: {
            return {
                loading: state.loading,
                assignments: state.assignments.concat([action.payload])
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["f" /* ActionTypes */].CREATE_ASSIGNMENT_SUCCESS: {
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
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["f" /* ActionTypes */].UPDATE_ASSIGNMENT: {
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
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["f" /* ActionTypes */].UPDATE_ASSIGNMENT_SUCCESS: {
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
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["f" /* ActionTypes */].DELETE_ASSIGNMENT: {
            console.log(state.assignments, action.payload);
            return {
                loading: false,
                assignments: state.assignments.filter(function (assignment) { return assignment.id !== action.payload.id; })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["f" /* ActionTypes */].LOAD_ASSIGNMENTS: {
            return {
                loading: true,
                assignments: []
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["f" /* ActionTypes */].LOAD_ASSIGNMENTS_SUCCESS: {
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

/***/ 612:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__app_actions__ = __webpack_require__(92);
/* harmony export (immutable) */ exports["a"] = reducer;

var initialState = {
    permissions: [],
    token: null
};
function reducer(state, action) {
    if (state === void 0) { state = initialState; }
    switch (action.type) {
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["f" /* ActionTypes */].LOAD_PERMISSIONS: {
            return state;
        }
        case __WEBPACK_IMPORTED_MODULE_0__app_actions__["f" /* ActionTypes */].LOAD_PERMISSIONS_SUCCESS: {
            return {
                permissions: action.payload.permissions ? action.payload.permissions : [],
                token: action.payload.token ? action.payload.token : null
            };
        }
        default: {
            return state;
        }
    }
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/users.js.map

/***/ },

/***/ 613:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__submission__ = __webpack_require__(168);
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
    function SubmissionDetailComponent() {
    }
    SubmissionDetailComponent.prototype.ngOnInit = function () {
    };
    __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Input"])(), 
        __metadata('design:type', (typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__submission__["a" /* Submission */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__submission__["a" /* Submission */]) === 'function' && _a) || Object)
    ], SubmissionDetailComponent.prototype, "submission", void 0);
    SubmissionDetailComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'app-submission-detail',
            template: __webpack_require__(825),
            styles: [__webpack_require__(797)]
        }), 
        __metadata('design:paramtypes', [])
    ], SubmissionDetailComponent);
    return SubmissionDetailComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-detail.component.js.map

/***/ },

/***/ 614:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_router__ = __webpack_require__(24);
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
    function SubmissionListComponent(router) {
        this.router = router;
    }
    SubmissionListComponent.prototype.ngOnInit = function () {
        console.log(this.submissions);
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
            template: __webpack_require__(828),
            styles: [__webpack_require__(800)]
        }), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__angular_router__["a" /* Router */]) === 'function' && _a) || Object])
    ], SubmissionListComponent);
    return SubmissionListComponent;
    var _a;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission-list.component.js.map

/***/ },

/***/ 615:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__ = __webpack_require__(179);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_rxjs_add_operator_mergeMap__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__ = __webpack_require__(166);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__submission_actions__ = __webpack_require__(119);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__submission_service__ = __webpack_require__(397);
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
            .map(function (submissionInfo) {
            Materialize.toast('Submission created', 1500);
            return __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["e" /* createSubmissionSuccess */])(submissionInfo.id);
        });
        // Update the submission on the server
        this.updateSubmission$ = this.actions$
            .ofType(__WEBPACK_IMPORTED_MODULE_3__submission_actions__["d" /* ActionTypes */].UPDATE_SUBMISSION)
            .mergeMap(function (action) {
            return _this.submissionService.updateSubmission(action.payload)
                .mergeMap(function (data) { return _this.submissionService.getSubmission(action.payload.id); });
        })
            .map(function (submission) {
            Materialize.toast('Submission updated', 1500);
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
    SubmissionEffects = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_1__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["b" /* Actions */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__ngrx_effects__["b" /* Actions */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_4__submission_service__["a" /* SubmissionService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_4__submission_service__["a" /* SubmissionService */]) === 'function' && _b) || Object])
    ], SubmissionEffects);
    return SubmissionEffects;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.effects.js.map

/***/ },

/***/ 616:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__submission_actions__ = __webpack_require__(119);
/* harmony export (immutable) */ exports["a"] = submissionReducer;

var initialState = {
    submissions: []
};
function submissionReducer(state, action) {
    if (state === void 0) { state = initialState; }
    switch (action.type) {
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].CREATE_SUBMISSION: {
            return {
                submissions: state.submissions.concat([action.payload])
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].CREATE_SUBMISSION_SUCCESS: {
            var submissionId_1 = action.payload.id ? Number(action.payload.id) : null;
            return {
                submissions: state.submissions.map(function (submission) {
                    if (!submission.id && submissionId_1) {
                        return Object.assign({}, submission, { id: submissionId_1 });
                    }
                    return submission;
                })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].UPDATE_SUBMISSION: {
            return {
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
                submissions: state.submissions.filter(function (submission) { return submission.id !== action.payload.id; })
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].LOAD_SUBMISSIONS: {
            return {
                submissions: []
            };
        }
        case __WEBPACK_IMPORTED_MODULE_0__submission_actions__["d" /* ActionTypes */].LOAD_SUBMISSIONS_SUCCESS: {
            return {
                submissions: action.payload ? action.payload : []
            };
        }
        default: {
            return state;
        }
    }
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/submission.reducer.js.map

/***/ },

/***/ 617:
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
            template: __webpack_require__(830),
            styles: [__webpack_require__(802)]
        }), 
        __metadata('design:paramtypes', [])
    ], UserComponent);
    return UserComponent;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/user.component.js.map

/***/ },

/***/ 618:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_forms__ = __webpack_require__(76);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__elmsln_service__ = __webpack_require__(65);
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
                newThis.uploadImage(base64)
                    .subscribe(function (image) {
                    console.log(image);
                    jQuery(_this).attr('src', image.url);
                    jQuery(_this).attr('width', image.metadata.width);
                    jQuery(_this).attr('height', image.metadata.height);
                    jQuery(_this).addClass('processed');
                }, function (error) {
                    jQuery(_this).remove();
                    Materialize.toast('Image must be smaller than 1024 x 640 pixels.', 2500);
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
    WysiwygjsComponent = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Component"])({
            selector: 'wysiwygjs',
            template: __webpack_require__(831),
            styles: [__webpack_require__(803)],
            providers: [
                {
                    provide: __WEBPACK_IMPORTED_MODULE_1__angular_forms__["b" /* NG_VALUE_ACCESSOR */],
                    useExisting: __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["forwardRef"])(function () { return WysiwygjsComponent; }),
                    multi: true
                }
            ]
        }), 
        __metadata('design:paramtypes', [(typeof (_c = typeof __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_0__angular_core__["ElementRef"]) === 'function' && _c) || Object, (typeof (_d = typeof __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */]) === 'function' && _d) || Object])
    ], WysiwygjsComponent);
    return WysiwygjsComponent;
    var _a, _b, _c, _d;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/wysiwygjs.component.js.map

/***/ },

/***/ 619:
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

/***/ 620:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_core_js_es6_symbol__ = __webpack_require__(636);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_core_js_es6_symbol___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_core_js_es6_symbol__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_core_js_es6_object__ = __webpack_require__(629);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1_core_js_es6_object___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_1_core_js_es6_object__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_core_js_es6_function__ = __webpack_require__(625);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_core_js_es6_function___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_2_core_js_es6_function__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_core_js_es6_parse_int__ = __webpack_require__(631);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_core_js_es6_parse_int___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3_core_js_es6_parse_int__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4_core_js_es6_parse_float__ = __webpack_require__(630);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4_core_js_es6_parse_float___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_4_core_js_es6_parse_float__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5_core_js_es6_number__ = __webpack_require__(628);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5_core_js_es6_number___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_5_core_js_es6_number__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6_core_js_es6_math__ = __webpack_require__(627);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6_core_js_es6_math___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_6_core_js_es6_math__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7_core_js_es6_string__ = __webpack_require__(635);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7_core_js_es6_string___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_7_core_js_es6_string__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8_core_js_es6_date__ = __webpack_require__(624);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8_core_js_es6_date___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_8_core_js_es6_date__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9_core_js_es6_array__ = __webpack_require__(623);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9_core_js_es6_array___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_9_core_js_es6_array__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10_core_js_es6_regexp__ = __webpack_require__(633);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_10_core_js_es6_regexp___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_10_core_js_es6_regexp__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11_core_js_es6_map__ = __webpack_require__(626);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_11_core_js_es6_map___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_11_core_js_es6_map__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12_core_js_es6_set__ = __webpack_require__(634);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_12_core_js_es6_set___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_12_core_js_es6_set__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_13_core_js_es6_reflect__ = __webpack_require__(632);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_13_core_js_es6_reflect___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_13_core_js_es6_reflect__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_14_core_js_es7_reflect__ = __webpack_require__(637);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_14_core_js_es7_reflect___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_14_core_js_es7_reflect__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_15_zone_js_dist_zone__ = __webpack_require__(1095);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_15_zone_js_dist_zone___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_15_zone_js_dist_zone__);
















//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/polyfills.js.map

/***/ },

/***/ 64:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__ngrx_store__ = __webpack_require__(13);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__elmsln_service__ = __webpack_require__(65);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__app_settings__ = __webpack_require__(117);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__assignment__ = __webpack_require__(249);
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
            .map(function (data) { return data.json().data; })
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
        return this.elmsln.post(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments/create', assignment)
            .map(function (data) { return data.json().node; })
            .map(function (node) { return Number(node.nid); });
    };
    AssignmentService.prototype.updateAssignment = function (assignment) {
        var _this = this;
        return this.elmsln.put(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments/' + assignment.id + '/update', assignment)
            .map(function (data) { return data.json().node; })
            .map(function (node) { return _this.convertToAssignment(node); });
    };
    AssignmentService.prototype.deleteAssignment = function (assignment) {
        return this.elmsln.delete(__WEBPACK_IMPORTED_MODULE_3__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/cle/assignments/' + assignment.id + '/delete')
            .map(function (data) { return data.json(); });
    };
    /**
     * @todo: this should eventually be more dynamic
     */
    AssignmentService.prototype.getAssignmentOptions = function () {
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
        return converted;
    };
    AssignmentService.prototype.prepareForDrupal = function (assignment) {
        // Convert date fields
        var newAssignment = {};
        // We have to construct a new assignment object to send to RESTws
        newAssignment.type = 'cle_assignment';
        if (assignment.title) {
            newAssignment.title = assignment.title;
        }
        if (assignment.project) {
            newAssignment.field_assignment_project = assignment.project;
        }
        if (assignment.type) {
            newAssignment.field_assignment_privacy_setting = assignment.type;
        }
        if (assignment.body) {
            newAssignment.field_assignment_description = {
                value: assignment.body
            };
        }
        if (assignment.critiqueMethod) {
            newAssignment.field_critique_method = assignment.critiqueMethod;
        }
        if (assignment.critiquePrivacy) {
            newAssignment.field_critique_privacy = assignment.critiquePrivacy;
        }
        if (assignment.critiqueStyle) {
            newAssignment.field_critique_style = assignment.critiqueStyle;
        }
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
                newAssignment.field_assignment_due_date = {
                    value: assignment.startDate,
                    value2: assignment.endDate
                };
            }
            else {
                newAssignment.field_assignment_due_date = {
                    value: assignment.endDate
                };
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
    AssignmentService = __decorate([
        __webpack_require__.i(__WEBPACK_IMPORTED_MODULE_0__angular_core__["Injectable"])(), 
        __metadata('design:paramtypes', [(typeof (_a = typeof __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_2__elmsln_service__["a" /* ElmslnService */]) === 'function' && _a) || Object, (typeof (_b = typeof __WEBPACK_IMPORTED_MODULE_1__ngrx_store__["a" /* Store */] !== 'undefined' && __WEBPACK_IMPORTED_MODULE_1__ngrx_store__["a" /* Store */]) === 'function' && _b) || Object])
    ], AssignmentService);
    return AssignmentService;
    var _a, _b;
}());
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/assignment.service.js.map

/***/ },

/***/ 65:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__(1);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_http__ = __webpack_require__(233);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__app_settings__ = __webpack_require__(117);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_ng2_cookies_ng2_cookies__ = __webpack_require__(441);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3_ng2_cookies_ng2_cookies___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_3_ng2_cookies_ng2_cookies__);
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__ngrx_store__ = __webpack_require__(13);
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
            name: 'testing',
            data: image
        };
        return this.post(__WEBPACK_IMPORTED_MODULE_2__app_settings__["a" /* AppSettings */].BASE_PATH + 'api/v1/elmsln/files/create', body)
            .map(function (data) { return data.json().file; });
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

/***/ 778:
/***/ function(module, exports) {

module.exports = ".cle-critique {\n  margin: 0 calc(-50vw + 50%);\n}"

/***/ },

/***/ 779:
/***/ function(module, exports) {

module.exports = ".assignment-dialog {\n  top: 5% !important;\n  bottom: 5% !important;\n  max-height: none !important;\n  height: 90%;\n}"

/***/ },

/***/ 780:
/***/ function(module, exports) {

module.exports = ".assignment-form {\n  max-width: 55em;\n  margin: auto;\n}\n\n.assignment-form > * {\n  margin-top: 2em;\n}\n\n.due-date .display {\n  font-size: 1.2em;\n  text-align: center;\n  margin: 1em;\n  color: gray;\n}\n\n.due-date .separator {\n  margin: 0 .5em;\n}\n\n:host >>> .wysiwyg-editor {\n  min-height: 10em;\n}\n\nselect {\n  display: block;\n}\n\n.critique {\n  padding: 1em;\n  padding-top: 2em;\n  background: rgba(0,0,0, 0.07);\n  position: relative;\n}\n.critique > * {\n  padding-bottom: 1em;\n}\n.critique > label:first-of-type {\n  position: absolute;\n  top: .5em;\n  left: .5em;\n}"

/***/ },

/***/ 781:
/***/ function(module, exports) {

module.exports = ".icon {\n  float: left;\n  margin-right: 1em;\n}\n\n.assignment:hover {\n  cursor: pointer;\n}\n\n.status {\n  float: right;\n  size: .9em;\n}\n@media (min-width: 500px) {\n  .status {\n    position: absolute;\n    top: 50%;\n    -webkit-transform: translateY(-50%);\n            transform: translateY(-50%);\n    right: 1em;\n  }\n}\n\n.status.complete {\n  color: green;\n}\n\n.add-button {\n  position: fixed;\n  top: 3.5em;\n  right: 3em;\n}\n\nnav, nav .btn {\n  background: transparent;\n  box-shadow: none;\n}\nnav li a {\n  color: #2196F3;\n}\n\n.assignment {\n  position: relative;\n}\n\n.assignment--loading {\n  background: #efefef;\n}\n\n.assignment:hover .assignment__edit-buttons {\n  opacity: 1;\n}\n\n.assignment__edit-buttons {\n  position: absolute;\n  right: 0;\n  top: 0;\n  background: -webkit-linear-gradient(left, transparent, white 30%);\n  background: linear-gradient(to right, transparent, white 30%);\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n  -webkit-box-align: center;\n      -ms-flex-align: center;\n          align-items: center;\n  -webkit-box-pack: end;\n      -ms-flex-pack: end;\n          justify-content: flex-end;\n  padding-left: 2em;\n  opacity: 0;\n  -webkit-transition: opacity .3s ease-in-out;\n  transition: opacity .3s ease-in-out;\n}\n\n.assignment__icons {\n  position: absolute;\n  right: 0;\n  top: 0;\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n  -webkit-box-align: center;\n      -ms-flex-align: center;\n          align-items: center;\n  -webkit-box-pack: end;\n      -ms-flex-pack: end;\n          justify-content: flex-end;\n  padding-left: 2em;\n}\n\n.assignment__icon--complete {\n  color: green;\n}"

/***/ },

/***/ 782:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 783:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 784:
/***/ function(module, exports) {

module.exports = ":host >>> .wysiwyg-editor {\n  min-height: 200px;\n}\n\n:host >>> .wysiwyg-container {\n  max-width: 900px;\n  margin: 1em;\n}"

/***/ },

/***/ 785:
/***/ function(module, exports) {

module.exports = ".created {\n  font-size: .9em;\n  opacity: .8;\n}\n\n.critique {\n  display: block;\n  overflow: hidden;\n}"

/***/ },

/***/ 786:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 787:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 788:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 789:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 790:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 791:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 792:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 793:
/***/ function(module, exports) {

module.exports = ".project {\n  margin: 1em;\n  padding: 1em;\n  background: lightgray;\n  width: auto;\n  position: relative;\n}\n\n.project__header {\n  position: relative;\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n}\n\n.project__options {\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n}\n.project__options > a {\n}\n\n.project__title-container {\n  width: 100%;\n}\n\n.project__title {\n  margin-top: 0;\n  font-size: 1.4em;\n}\n\n.project__board {\n  padding: 1em;\n  min-height: 200px;\n  width: 100%;\n}\n\n.assignment {\n  background: white;\n  padding: 1em;\n  width: 100%;\n}\n\n.assignment__title {\n  margin-top: 0;\n  font-size: 1.4em;\n}"

/***/ },

/***/ 794:
/***/ function(module, exports) {

module.exports = ".projects-container {\n  display: -webkit-box;\n  display: -ms-flexbox;\n  display: flex;\n  width: auto;\n  -webkit-box-align: center;\n      -ms-flex-align: center;\n          align-items: center;\n  -webkit-box-pack: start;\n      -ms-flex-pack: start;\n          justify-content: flex-start;\n  -webkit-box-align: start;\n      -ms-flex-align: start;\n          align-items: flex-start;\n  overflow-x: scroll;\n  margin: 0 calc(-50vw + 50%);\n}\n\n.projects-container >>> app-project-item {\n  width: 100%;\n  min-width: 400px;\n  max-width: 500px;\n}\n\n.create-project {\n  margin: 3em auto;\n  max-width: 300px;\n  display: block;\n  cursor: pointer;\n}\n\n.face {\n  text-align: center;\n  margin: auto;\n  display: block;\n  font-size: 5em;\n  margin-bottom: 2rem;\n  margin-top: 2rem;\n  color: #ababab;\n}\n\n.preloader-wrapper {\n  position: absolute;\n  top: 50%;\n  left: 50%;\n}"

/***/ },

/***/ 795:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 796:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 797:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 798:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 799:
/***/ function(module, exports) {

module.exports = ":host >>> .wysiwyg-editor {\n  min-height: 10em;\n}\n\n.actions {\n  padding-top: 2em;\n}"

/***/ },

/***/ 800:
/***/ function(module, exports) {

module.exports = ".collection-item {\n  cursor: pointer;\n}"

/***/ },

/***/ 801:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 802:
/***/ function(module, exports) {

module.exports = ""

/***/ },

/***/ 803:
/***/ function(module, exports) {

module.exports = "/* CSS for the font-name + font-size plugin */\n.wysiwyg-plugin-list {\n    max-height: 16em;\n    overflow: auto;\n    overflow-x: hidden;\n    overflow-y: scroll;\n}\n.wysiwyg-plugin-list a,\n.wysiwyg-plugin-list a:link,\n.wysiwyg-plugin-list a:visited {\n    display: block;\n    color: black;\n    padding: 5px 10px;\n    text-decoration: none;\n    cursor: pointer;\n}\n.wysiwyg-plugin-list a:hover {\n    color: HighlightText;\n    background-color: Highlight;\n}\n/* CSS for the smiley plugin */\n.wysiwyg-plugin-smilies {\n    padding: 10px;\n    text-align: center;\n    white-space: normal;\n}\n.wysiwyg-plugin-smilies img {\n    display: -moz-inline-stack; /* inline-block: http://blog.mozilla.org/webdev/2009/02/20/cross-browser-inline-block/ */\n    display: inline-block;\n    *display: inline;\n}\n\n.wysiwyg-browse {\n  height: 50%;\n}\n\n.wysiwyg-editor img {\n    height:auto;\n    max-width: 100%;\n}"

/***/ },

/***/ 806:
/***/ function(module, exports) {

module.exports = "<div class=\"cle-critique\">\n  <div class=\"container\">\n    <router-outlet></router-outlet>\n    <router-outlet name=\"dialog\"></router-outlet>\n  </div>\n</div>"

/***/ },

/***/ 807:
/***/ function(module, exports) {

module.exports = "<!-- Modal Structure -->\n<div id=\"modal-assignment-dialog\" class=\"modal modal-fixed-footer assignment-dialog\">\n\n  <!--Create or Update Assignment-->\n  <div *ngIf=\"action === 'create' || action === 'update'\">\n    <div class=\"modal-content\">\n      <h2 *ngIf=\"assignment.id\">Edit Assignment</h2>\n      <h2 *ngIf=\"!assignment.id\">Create Assignment</h2>\n      <app-assignment-form [assignment]=\"assignment\" (assignmentSave)=\"onAssignmentSave($event)\"></app-assignment-form>\n    </div>\n    <div class=\"modal-footer\">\n      <a (click)=\"onSave()\" class=\"modal-action modal-close waves-effect waves-green btn-flat\">Save</a>\n      <a (click)=\"onCancel()\" class=\" modal-action modal-close waves-effect waves-green btn-flat\">Cancel</a>\n    </div>\n  </div>\n\n  <!--DELETE Assignment-->\n  <div *ngIf=\"action === 'delete'\">\n    <div class=\"modal-content\">\n      <h2>Are you sure you want to delete this assignment?</h2>\n      <p>The following assignment will be deleted: {{ assignment.title }}</p>\n      <p>Are you sure you want to proceed?</p>\n    </div>\n    <div class=\"modal-footer\">\n      <a (click)=\"onDelete()\" class=\"modal-action modal-close waves-effect waves-red btn-flat\">Delete</a>\n      <a (click)=\"onCancel()\" class=\" modal-action modal-close waves-effect waves-green btn-flat\">Cancel</a>\n    </div>\n  </div>\n</div>\n"

/***/ },

/***/ 808:
/***/ function(module, exports) {

module.exports = "<form [formGroup]=\"form\" class=\"assignment-form\">\n  <input formControlName=\"title\" placeholder=\"Title\">\n  <wysiwygjs formControlName=\"body\"></wysiwygjs>\n\n  <div class=\"privacy\">\n    <label>Privacy Setting:</label>\n    <select formControlName=\"type\">\n      <option value=\"\" disabled selected>Choose your option</option>\n      <option *ngFor=\"let option of assignmentOptions.type\" [value]=\"option.value\">{{ option.display }}</option>\n    </select>\n  </div>\n\n  <div class=\"critique\">\n    <label>Critique settings</label>\n\n    <div class=\"critique-method\">\n      <label>Method</label>\n      <select formControlName=\"critiqueMethod\">\n        <option *ngFor=\"let option of assignmentOptions.critiqueMethod\" [value]=\"option.value\">{{ option.display }}</option>\n      </select>\n    </div>\n\n    <div class=\"critique-style\">\n      <label>Critique style</label>\n      <select formControlName=\"critiqueStyle\">\n        <option *ngFor=\"let option of assignmentOptions.critiqueStyle\" [value]=\"option.value\">{{ option.display }}</option>\n      </select>\n    </div>\n\n    <div class=\"critique-privacy switch\">\n      <label>\n        Private\n        <input type=\"checkbox\" formControlName=\"critiquePrivacy\">\n        <span class=\"lever\"></span>\n        Public\n      </label>\n    </div>\n\n  </div>\n\n  <div class=\"due-date\">\n    <div class=\"display\" *ngIf=\"form.value.endDate !==null\">\n      Due date:\n      <span *ngIf=\"form.value.startDate !== null\" class=\"start-date\">\n        {{ form.value.startDate | amDateFormat:'LL hh:mma' }} \n        <span class=\"separator\">\n          to\n        </span>\n      </span>\n      <span class=\"end-date\">\n        {{ form.value.endDate | amDateFormat:'LL hh:mma' }}\n      </span>\n    </div>\n    \n    <div *ngIf=\"form.value.endDate !== null\" class=\"start-date\">\n      <label>Start Date</label>\n      <app-datetime-input formControlName=\"startDate\"></app-datetime-input>\n    </div>\n\n    <div class=\"due-date\">\n      <label>Due Date</label>\n      <app-datetime-input formControlName=\"endDate\"></app-datetime-input>\n    </div>\n  </div>\n</form>"

/***/ },

/***/ 809:
/***/ function(module, exports) {

module.exports = "<div class=\"row\">\n  <ul class=\"collapsible\">\n    <li *ngFor=\"let assignment of assignments\">\n      <div class=\"collapsible-header assignment\" [ngClass]=\"{'assignment--loading': !assignment.id}\">\n        <div class=\"assignment__body\" (click)=\"viewAssignment(assignment.id)\">\n          <i class=\"material-icons\">assignment</i>{{ assignment.title }}\n          <span *ngIf=\"assignment.complete == 1\" class=\"badge green-text\">Complete</span>\n          <span *ngIf=\"assignment.complete == 0\" class=\"badge red-text\">Incomplete</span>\n          <div class=\"due-dates\">\n            <span *ngIf=\"assignment.startDate\">{{ assignment.startDate | amDateFormat:'MM/DD/YY' }} - </span>\n            {{ assignment.endDate | amDateFormat:'MM/DD/YY' }}\n          </div>\n        </div>\n        <div class=\"assignment__icons\">\n          <span *ngIf=\"assignment && assignment.metadata.relatedSubmissions && assignment.metadata.relatedSubmissions.complete.status\" class=\"assignment__icon--complete\"><i class=\"material-icons\">check</i></span>\n        </div>\n        <div class=\"assignment__edit-buttons\" *ngIf=\"assignment.id && (userCanEdit$ | async)\">\n          <a (click)=\"onEditAssignment(assignment)\"><i class=\"material-icons\" aria-label=\"Edit assignment\">edit</i></a>\n          <a (click)=\"onDeleteAssignment(assignment)\"><i class=\"material-icons\" aria-label=\"Edit assignment\">delete</i></a>\n        </div>\n        <div class=\"assignment__loading\" *ngIf=\"!assignment.id\">\n          <div class=\"progress\">\n            <div class=\"indeterminate\"></div>\n          </div>\n        </div>\n      </div>\n    </li>\n  </ul>\n</div>"

/***/ },

/***/ 810:
/***/ function(module, exports) {

module.exports = "<div *ngFor=\"let assignment of (assignments$| async)\">\n    <nav>\n      <div class=\"nav-wrapper\">\n        <ul id=\"nav-mobile\" class=\"left\">\n          <li><a routerLink=\"/projects\"><i class=\"material-icons left\">&#xE5C4;</i> projects</a></li>\n        </ul>\n        <ul id=\"nav-mobile\" class=\"right\">\n          <li *ngIf=\"(userCanEdit$ | async)\"><a (click)=\"onEditAssignment(assignment)\" title=\"Edit this assignment\"><i class=\"material-icons left\">edit</i></a></li>\n        </ul>\n      </div>\n    </nav>\n\n    <div class=\"assignment\" *ngIf=\"assignment\">\n      <h1 class=\"assignment__title\">{{ assignment.title }}</h1>\n      <div class=\"assignment__meta\">\n        <div class=\"assignment__dates\">\n          <span *ngIf=\"assignment.startDate\">{{ assignment.startDate | amDateFormat:'LL hh:mmA' }} - </span>\n          {{ assignment.endDate | amDateFormat:'LL hh:mmA' }}\n        </div>\n      </div>\n      <div class=\"assignment__description\" [innerHTML]=\"assignment.body\"> </div>\n    </div>\n\n\n  <app-submission-list *ngIf=\"(submissions$ | async).length > 0\" title=\"My Submission\" [submissions]=\"submissions$ | async\"></app-submission-list>\n\n  <a *ngIf=\"assignment && assignment.metadata.canCreate && !assignment.metadata.complete.status\" (click)=\"onCreateSubmission(assignment)\" class=\"btn-large\">Submit assignment</a>\n  <a *ngIf=\"assignment && !assignment.metadata.canCreate\" class=\"btn-large disabled\">Submit assignment</a>\n</div>"

/***/ },

/***/ 811:
/***/ function(module, exports) {

module.exports = "<!-- Dropdown Trigger -->\n<a class='dropdown-button' href='#' data-activates='dropdown1'><i class=\"material-icons text-black\">more_vert</i></a>\n<!-- Dropdown Structure -->\n<ul id='dropdown1' class='dropdown-content'>\n  <li><a href=\"#!\">one</a></li>\n  <li><a href=\"#!\">two</a></li>\n  <li class=\"divider\"></li>\n  <li><a href=\"#!\">three</a></li>\n</ul>"

/***/ },

/***/ 812:
/***/ function(module, exports) {

module.exports = "<wysiwygjs (onFocus)=\"onFocus($event)\" (onChange)=\"onChange($event)\" (onBlur)=\"onBlur($event)\"></wysiwygjs>\n\n\n<button md-raised-button (click)=\"submitForm()\" color=\"primary\">Submit Critique</button>"

/***/ },

/***/ 813:
/***/ function(module, exports) {

module.exports = "critiques list works!"

/***/ },

/***/ 814:
/***/ function(module, exports) {

module.exports = "critique.component"

/***/ },

/***/ 815:
/***/ function(module, exports) {

module.exports = "<p>\n  dashboard works!\n</p>\n"

/***/ },

/***/ 816:
/***/ function(module, exports) {

module.exports = "<div>\n  <input [(ngModel)]=\"day\" (ngModelChange)=\"updateDatetime($event)\" type=\"date\" class=\"datepicker\">\n  <input [(ngModel)]=\"time\" (ngModelChange)=\"updateDatetime($event)\" type=\"time\">\n</div>"

/***/ },

/***/ 817:
/***/ function(module, exports) {

module.exports = "<div *ngIf=\"editing\">\n  <form [formGroup]=\"form\">\n    <input formControlName=\"content\" (keyup.enter)=\"endEditing()\" type=\"text\" class=\"text-input\"> \n  </form>\n</div>\n<div *ngIf=\"editing == false\" (click)=\"beginEditing()\">\n  <ng-content></ng-content>\n</div>\n"

/***/ },

/***/ 818:
/***/ function(module, exports) {

module.exports = "<form [formGroup]=\"form\" id=\"login-form\" class=\"input-field col s12\">\n  <input formControlName=\"username\" id=\"critique-form-username\" name=\"critique-form-username\" placeholder=\"username\"/>\n  <input formControlName=\"password\" id=\"critique-form-password\" name=\"critique-form-password\" placeholder=\"password\"/>\n</form>\n<button (click)=\"submitForm()\" class=\"btn\" color=\"primary\">Login</button>"

/***/ },

/***/ 819:
/***/ function(module, exports) {

module.exports = "<p>\n  logout works!\n</p>\n"

/***/ },

/***/ 820:
/***/ function(module, exports) {

module.exports = "<p>\n  project-card works!\n</p>\n"

/***/ },

/***/ 821:
/***/ function(module, exports) {

module.exports = "<div class=\"project\">\n  <div class=\"project__header\">\n    <div class=\"project__title-container\">\n\n      <app-editable-field *ngIf=\"(userCanEdit$ | async)\" [type]=\"text\" [content]=\"project.title\" (contentUpdated)=\"updateTitle($event)\">\n        <h1 class=\"project__title\">{{ project.title }}</h1>\n      </app-editable-field>\n      <h1 *ngIf=\"!(userCanEdit$ | async)\" class=\"project__title\">{{ project.title }}</h1>\n\n      <div class=\"project__description\" [innerHTML]=\"project.description\"></div>\n    </div>\n    <div *ngIf=\"(userCanEdit$ | async)\" class=\"project__options\"> \n      <a (click)=\"onCreateAssignment()\" class=\"waves-effect btn-flat tooltipped\" data-tooltip=\"create assignment\"><i class=\"material-icons\">add</i></a>\n      <a (click)=\"onDeleteProject()\" class=\"waves-effect btn-flat tooltipped\" data-tooltip=\"delete assignment\"><i class=\"material-icons\">delete</i></a>\n    </div>\n  </div>\n  <div class=\"project__board\">\n    <cle-assignment-list [assignments]=\"assignments | async\"></cle-assignment-list>\n  </div>\n</div>\n\n<div id=\"modal-{{project.id}}\" class=\"modal delete-project-form\">\n  <div class=\"modal-content\">\n    <h4>Delete project confirmation</h4>\n    <p>Are you sure you want to delete the project titled \"{{ project.title }}\"?</p>\n  </div>\n  <div class=\"modal-footer\">\n    <a (click)=\"confirmDelete(false)\" class=\"modal-action modal-close waves-effect waves-green btn-flat\">Cancel</a>\n    <a (click)=\"confirmDelete(true)\" class=\" modal-action modal-close waves-effect waves-red btn-flat\">Delete</a>\n  </div>\n</div>"

/***/ },

/***/ 822:
/***/ function(module, exports) {

module.exports = "<div *ngIf=\"loading === true\" class=\"preloader-wrapper big active\">\n  <div class=\"spinner-layer spinner-blue-only\">\n    <div class=\"circle-clipper left\">\n      <div class=\"circle\"></div>\n    </div><div class=\"gap-patch\">\n      <div class=\"circle\"></div>\n    </div><div class=\"circle-clipper right\">\n      <div class=\"circle\"></div>\n    </div>\n  </div>\n</div>\n\n<div *ngIf=\"(userCanEdit$ | async)\"> \n  <a (click)=\"createNewProject('Add project')\" class=\"create-project waves-effect waves-light btn-large\"><i class=\"material-icons right\">add</i>New project</a>\n</div>\n\n<div class=\"projects-container\">\n  <app-project-item *ngFor=\"let project of (projects$ | async)\" [project]=\"project\" (delete)=\"projectDeleted(project)\"></app-project-item>\n</div>\n\n"

/***/ },

/***/ 823:
/***/ function(module, exports) {

module.exports = "<p>\n  projects works!\n</p>\n"

/***/ },

/***/ 824:
/***/ function(module, exports) {

module.exports = "<div class=\"submission-create\">\n  <app-submission-form [submission]=\"submission\" (onSubmissionSave)=\"onSubmissionSave($event)\" (onSubmissionCancel)=\"onSubmissionCancel($event)\"></app-submission-form>\n</div>"

/***/ },

/***/ 825:
/***/ function(module, exports) {

module.exports = "<div class=\"submission-detail\" *ngIf=\"submission\">\n  <h1>{{ submission.title }}</h1>\n  <div class=\"body\" [innerHTML]=\"submission.body\"></div>\n</div>"

/***/ },

/***/ 826:
/***/ function(module, exports) {

module.exports = "<div class=\"submission-edit\">\n  <app-submission-form *ngIf=\"submission$ | async\" [submission]=\"submission$ | async\" (onSubmissionSave)=\"onSubmissionSave($event)\" (onSubmissionCancel)=\"onSubmissionCancel($event)\" (onFormChanges)=\"onFormChanges($event)\"></app-submission-form>\n</div>"

/***/ },

/***/ 827:
/***/ function(module, exports) {

module.exports = "<form *ngIf=\"form\" [formGroup]=\"form\" class=\"submission-form\">\n  <input formControlName=\"title\" placeholder=\"title\">\n  <wysiwygjs formControlName=\"body\" (onWysiwygInit)=\"onWysiwygInit()\"></wysiwygjs>\n\n  <div class=\"actions\">\n    <button type=\"submit\" class=\"btn\" (click)=\"submit()\">Save</button>\n    <button type=\"submit\" class=\"btn\" (click)=\"cancel()\">Cancel</button>\n  </div>\n</form>\n"

/***/ },

/***/ 828:
/***/ function(module, exports) {

module.exports = "<ul class=\"submission-list collection with-header\">\n  <li class=\"collection-header\" *ngIf=\"title\"><h4>{{title}}</h4></li>\n  <li *ngFor=\"let submission of submissions\" class=\"collection-item\" (click)=\"onSubmissionClick(submission)\">{{ submission.title }}</li>\n</ul>"

/***/ },

/***/ 829:
/***/ function(module, exports) {

module.exports = "<nav>\n  <div class=\"nav-wrapper\">\n    <ul id=\"nav-mobile\" class=\"left\">\n      <li><a (click)=\"onClickBack()\"><i class=\"material-icons left\">&#xE5C4;</i> assignment</a></li>\n    </ul>\n    <ul id=\"nav-mobile-right\" class=\"right\">\n      <li><a (click)=\"editSubmission()\"><i class=\"material-icons left\">edit</i></a></li>\n    </ul>\n  </div>\n</nav>\n\n<div *ngIf=\"submissionId\">\n  <app-submission-detail [submission]=\"submission$ | async\"></app-submission-detail>\n</div>"

/***/ },

/***/ 830:
/***/ function(module, exports) {

module.exports = "<p>\n  user works!\n</p>\n"

/***/ },

/***/ 831:
/***/ function(module, exports) {

module.exports = "<textarea>{{ content }}</textarea>"

/***/ },

/***/ 92:
/***/ function(module, exports, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(exports, "f", function() { return ActionTypes; });
/* harmony export (immutable) */ exports["d"] = createAssignment;
/* harmony export (immutable) */ exports["g"] = createAssignmentSuccess;
/* harmony export (immutable) */ exports["c"] = updateAssignment;
/* harmony export (immutable) */ exports["h"] = updateAssignmentSuccess;
/* harmony export (immutable) */ exports["e"] = deleteAssignment;
/* harmony export (immutable) */ exports["b"] = loadAssignments;
/* harmony export (immutable) */ exports["i"] = loadAssignmentsSuccess;
/* harmony export (immutable) */ exports["a"] = loadPermissions;
/* harmony export (immutable) */ exports["j"] = loadPermissionsSuccess;
var ActionTypes = {
    CREATE_ASSIGNMENT: 'CREATE_ASSIGNMENT',
    CREATE_ASSIGNMENT_SUCCESS: 'CREATE_ASSIGNMENT_SUCCESS',
    UPDATE_ASSIGNMENT: 'UPDATE_ASSIGNMENT',
    UPDATE_ASSIGNMENT_SUCCESS: 'UPDATE_ASSIGNMENT_SUCCESS',
    DELETE_ASSIGNMENT: 'DELETE_ASSIGNMENT',
    LOAD_ASSIGNMENTS: 'LOAD_ASSIGNMENTS',
    LOAD_ASSIGNMENTS_SUCCESS: 'LOAD_ASSIGNMENTS_SUCCESS',
    LOAD_PERMISSIONS: 'LOAD_PERMISSIONS',
    LOAD_PERMISSIONS_SUCCESS: 'LOAD_PERMISSIONS_SUCCESS'
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
function loadPermissionsSuccess(permissions, token) {
    return {
        type: ActionTypes.LOAD_PERMISSIONS_SUCCESS,
        payload: { permissions: permissions, token: token }
    };
}
//# sourceMappingURL=/Users/scienceonlineed/Documents/websites/elmsln/core/dslmcode/profiles/cle-7.x-2.x/modules/features/cle_app/app/src/app.actions.js.map

/***/ }

},[1097]);
//# sourceMappingURL=main.bundle.map